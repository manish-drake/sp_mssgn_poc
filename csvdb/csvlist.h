#ifndef CSVLIST_H
#define CSVLIST_H
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

const char DL[] = ",";
const int MAX_ROW_SZ = 1024;
enum filterOperand
{
    EqualTo,
    NotEqualTo,
    LessThan,
    LessThanEqualTo,
    GreaterThan,
    GreaterThanEqualTo
};
struct filter
{
    const char *lhs;
    filterOperand operand;
    const char *rhs;
};

class CSVList
{
public:
    using row = std::vector<std::string>;
private:
    struct csv
    {
        row m_row;
        row* m_fields;
        std::string toString()
        {
            std::string strRow = "";
            for (const auto &col : m_row)
            {
                strRow += col;
                strRow += ",";
            }
            strRow.pop_back();
            return strRow;
        }
        csv(const row &arg, row *fields) : m_row{arg},
                                           m_fields{fields}
        {
        }

        int colIndex(const std::string &colName) const
        {
            int index = 0;
            for (auto &field : *m_fields)
            {
                if (field == colName)
                    return index;
                index += 1;
            }
            return -1;
        }
        std::string &operator[](const int &index)
        {
            return m_row[index];
        }
        const std::string &operator[](const int &index) const
        {
            return m_row[index];
        }
        std::string *operator[](const std::string &fieldName)
        {
            int index = colIndex(fieldName);
            if (index >= 0)
                return &m_row[index];
            else
                return nullptr;
        }
        const std::string *operator[](const std::string &fieldName) const
        {
            int index = colIndex(fieldName);
            if (index >= 0)
                return &m_row[index];
            else
                return nullptr;
        }
        bool trySet(const char* fieldName, const char* value)
        {
            int index = colIndex(fieldName);
            if (index >= 0)
            {
                m_row[index] = value;
                return true;
            }
            else
                return false;
        }
    };
    using rows = std::vector<csv>;
    using const_row_iterator = rows::const_iterator;
    using row_iterator = rows::iterator;

    row m_fields;
    rows m_rows;

    std::string *get(const row::size_type &row, const row::size_type &col);
    std::string *get(const row::size_type &row, const std::string &fieldName);
    std::string toString()
    {
        std::string strRow;
        for (const auto &col : m_fields)
        {
            strRow += col;
            strRow += ",";
        }
        strRow.pop_back();
        return strRow;
    }

public:
    static void split(const char *str, const char *delimitter, row *collection);
    using prows = std::vector<csv *>;

private:
    prows m_filteredList;
    prows Filter(const filter &filter, CSVList::prows &rows);
    prows &Filter(const filter &filter, CSVList::rows &rows);

public:
    CSVList();
    CSVList(const char *fields);
    void Add(const char *data);
    // const_row_iterator begin() const
    // {
    //     return m_rows.cbegin();
    // }
    // const_row_iterator end() const
    // {
    //     return m_rows.cend();
    // }
    csv* begin() { return &m_rows[0]; }
    const csv* begin() const { return &m_rows[0]; }
    csv* end() { return &m_rows[m_rows.size()]; }
    const csv* end() const { return &m_rows[m_rows.size()]; }

    void Save(const char *filename);
    void Open(const char *filename);
    prows &Filter(const std::vector<filter> &filters);

    std::string *operator[](const std::string &fieldName)
    {
        if (m_filteredList.size() > 0)
        {
            auto &csv = *m_filteredList.front();
            return csv[fieldName];
        }
        else
        {
            if (m_rows.size() > 0)
            {
                auto &csv = m_rows.front();
                return csv[fieldName];
            }
            else
            {
                return nullptr;
            }
        }
    }
    const std::string *operator[](const std::string &fieldName) const
    {
        return this->operator[](fieldName);
    }
};

#endif // CSVLIST_H
