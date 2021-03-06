// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_UTILS_INI_HPP
#define OUZEL_UTILS_INI_HPP

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iterator>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "utils/UTF8.hpp"

namespace ouzel
{
    namespace ini
    {
        class Data;

        class Section final
        {
            friend Data;
        public:
            Section() {}

            Section(const std::string& initName):
                name(initName)
            {
            }

            inline const std::string& getName() const { return name; }
            inline void setName(const std::string& newName) { name = newName; }

            inline const std::map<std::string, std::string>& getValues() const { return values; }

            inline bool hasValue(const std::string& key) const
            {
                auto valueIterator = values.find(key);
                return valueIterator != values.end();
            }

            const std::string& getValue(const std::string& key)
            {
                return values[key];
            }

            std::string getValue(const std::string& key) const
            {
                auto valueIterator = values.find(key);
                if (valueIterator != values.end())
                    return valueIterator->second;

                return std::string();
            }

            const std::string& getValue(const std::string& key, const std::string& defaultValue) const
            {
                auto valueIterator = values.find(key);

                if (valueIterator != values.end())
                    return valueIterator->second;

                return defaultValue;
            }

            void setValue(const std::string& key, const std::string& value)
            {
                values[key] = value;
            }

            void deleteValue(const std::string& key)
            {
                auto valueIterator = values.find(key);

                if (valueIterator != values.end())
                    values.erase(valueIterator);
            }

        private:
            void encode(std::vector<uint8_t>& data) const
            {
                if (!name.empty())
                {
                    data.push_back('[');
                    data.insert(data.end(), name.begin(), name.end());
                    data.push_back(']');
                    data.push_back('\n');
                }

                for (const auto& value : values)
                {
                    data.insert(data.end(), value.first.begin(), value.first.end());
                    data.push_back('=');
                    data.insert(data.end(), value.second.begin(), value.second.end());
                    data.push_back('\n');
                }
            }

            std::string name;
            std::map<std::string, std::string> values;
        };

        static inline bool isWhitespace(uint32_t c)
        {
            return c == ' ' || c == '\t';
        }

        inline std::vector<uint32_t>& ltrimUtf32(std::vector<uint32_t>& s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                            std::not1(std::ptr_fun<uint32_t, bool>(isWhitespace))));
            return s;
        }

        inline std::vector<uint32_t>& rtrimUtf32(std::vector<uint32_t>& s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 std::not1(std::ptr_fun<uint32_t, bool>(isWhitespace))).base(), s.end());
            return s;
        }

        inline std::vector<uint32_t>& trimUtf32(std::vector<uint32_t>& s)
        {
            return ltrimUtf32(rtrimUtf32(s));
        }

        class Data final
        {
        public:
            Data()
            {
            }

            Data(const std::vector<uint8_t>& data)
            {
                std::vector<uint32_t> str;

                // BOM
                if (data.size() >= 3 &&
                    data[0] == 0xEF &&
                    data[1] == 0xBB &&
                    data[2] == 0xBF)
                {
                    bom = true;
                    str = utf8::toUtf32(std::vector<uint8_t>(data.begin() + 3, data.end()));
                }
                else
                {
                    bom = false;
                    str = utf8::toUtf32(data);
                }

                auto result = sections.insert(std::make_pair("", Section())); // default section
                auto sectionIterator = result.first;

                for (auto iterator = str.begin(); iterator != str.end();)
                {
                    if (isWhitespace(*iterator) || *iterator == '\n' || *iterator == '\r') // line starts with a whitespace
                        ++iterator; // skip the white space
                    else if (*iterator == '[') // section
                    {
                        ++iterator; // skip the left bracket

                        std::vector<uint32_t> sectionUtf32;
                        bool parsedSection = false;

                        for (;;)
                        {
                            if (iterator == str.end() || *iterator == '\n' || *iterator == '\r')
                            {
                                if (!parsedSection)
                                    throw std::runtime_error("Unexpected end of section");

                                ++iterator; // skip the newline
                                break;
                            }
                            else if (*iterator == ';')
                            {
                                ++iterator; // skip the semicolon

                                if (!parsedSection)
                                    throw std::runtime_error("Unexpected comment");

                                for (;;)
                                {
                                    if (iterator == str.end())
                                        break;
                                    else if (*iterator == '\n' || *iterator == '\r')
                                    {
                                        ++iterator; // skip the newline
                                        break;
                                    }

                                    ++iterator;
                                }
                                break;
                            }
                            else if (*iterator == ']')
                                parsedSection = true;
                            else if (*iterator != ' ' && *iterator != '\t')
                            {
                                if (parsedSection)
                                    throw std::runtime_error("Unexpected character after section");
                            }

                            if (!parsedSection)
                                sectionUtf32.push_back(*iterator);

                            ++iterator;
                        }

                        trimUtf32(sectionUtf32);

                        if (sectionUtf32.empty())
                            throw std::runtime_error("Invalid section name");

                        std::string section = utf8::fromUtf32(sectionUtf32);

                        result = sections.insert(std::make_pair(section, Section(section)));
                        sectionIterator = result.first;
                    }
                    else if (*iterator == ';') // comment
                    {
                        while (++iterator != str.end())
                        {
                            if (*iterator == '\r' || *iterator == '\n')
                            {
                                ++iterator; // skip the newline
                                break;
                            }
                        }
                    }
                    else // key, value pair
                    {
                        std::vector<uint32_t> keyUtf32;
                        std::vector<uint32_t> valueUtf32;
                        bool parsedKey = false;

                        for (;;)
                        {
                            if (iterator == str.end())
                                break;
                            else if (*iterator == '\r' || *iterator == '\n')
                            {
                                ++iterator; // skip the newline
                                break;
                            }
                            else if (*iterator == '=')
                            {
                                if (!parsedKey)
                                    parsedKey = true;
                                else
                                    throw std::runtime_error("Unexpected character");
                            }
                            else if (*iterator == ';')
                            {
                                ++iterator; // skip the semicolon

                                for (;;)
                                {
                                    if (iterator == str.end())
                                        break;
                                    else if (*iterator == '\r' || *iterator == '\n')
                                    {
                                        ++iterator; // skip the newline
                                        break;
                                    }

                                    ++iterator;
                                }
                                break;
                            }
                            else
                            {
                                if (!parsedKey)
                                    keyUtf32.push_back(*iterator);
                                else
                                    valueUtf32.push_back(*iterator);
                            }

                            ++iterator;
                        }

                        if (keyUtf32.empty())
                            throw std::runtime_error("Invalid key name");

                        keyUtf32 = trimUtf32(keyUtf32);
                        valueUtf32 = trimUtf32(valueUtf32);

                        std::string key = utf8::fromUtf32(keyUtf32);
                        std::string value = utf8::fromUtf32(valueUtf32);

                        sectionIterator->second.values[key] = value;
                    }
                }
            }

            std::vector<uint8_t> encode() const
            {
                std::vector<uint8_t> result;

                if (bom) result = {0xEF, 0xBB, 0xBF};

                auto i = sections.find("");
                if (i != sections.end())
                    i->second.encode(result);

                for (const auto& section : sections)
                {
                    if (!section.first.empty())
                        section.second.encode(result);
                }

                return result;
            }

            inline const std::map<std::string, Section>& getSections() const { return sections; }

            inline bool hasSection(const std::string& name) const
            {
                auto sectionIterator = sections.find(name);
                return sectionIterator != sections.end();
            }

            inline Section& getSection(const std::string& name)
            {
                return sections[name];
            }

            Section getSection(const std::string& name) const
            {
                auto sectionIterator = sections.find(name);
                if (sectionIterator != sections.end())
                    return sectionIterator->second;

                return Section();
            }

            inline void setSection(const std::string& name, const Section& section)
            {
                sections[name] = section;
            }

            void deleteSection(const std::string& name)
            {
                auto sectionIterator = sections.find(name);
                if (sectionIterator != sections.end())
                    sections.erase(sectionIterator);
            }

            inline bool hasBOM() const { return bom; }
            inline void setBOM(bool newBOM) { bom = newBOM; }

        private:
            bool bom = false;
            std::map<std::string, Section> sections;
        };
    } // namespace ini
} // namespace ouzel

#endif // OUZEL_UTILS_INI_HPP
