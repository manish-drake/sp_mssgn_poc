#include "csvlist.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <sstream>

CSVList::CSVList()
{
}

CSVList::CSVList(const char *fields) : CSVList()
{
    std::cout << "CSV List Created" << std::endl;
    split(fields, DL, &m_fields);
}

void CSVList::split(const char *str, const char *delimitter, row *collection)
{
    collection->clear();
    std::stringstream ss(str);
    std::string elem;
    while (std::getline(ss, elem, delimitter[0]))
    {
        collection->push_back(std::move(elem));
    }
}

std::string *CSVList::get(const row::size_type &row, const row::size_type &col)
{
    return &m_rows[row][col];
}

std::string *CSVList::get(const row::size_type &row, const std::string &fieldName)
{
    return m_rows[row][fieldName];
}

void CSVList::Add(const char *data)
{
    m_rows.push_back(csv(row(), &m_fields));
    auto &newRow = m_rows[m_rows.size() - 1].m_row;
    split(data, DL, &newRow);
}

void CSVList::Save(const char *filename)
{
    auto fp = fopen(filename, "w+");

    fprintf(fp, "%s\n", toString().c_str());
    for (auto &each : m_rows)
    {
        fprintf(fp, "%s\n", each.toString().c_str());
    }
    fclose(fp);
}
void CSVList::Open(const char *filename)
{
    m_fields.clear();
    m_rows.clear();
    auto fp = fopen(filename, "r");
    char rowBuff[MAX_ROW_SZ] = {0};
    if (fgets(rowBuff, MAX_ROW_SZ, (FILE *)fp))
    {
        rowBuff[strcspn(rowBuff, "\n")] = '\0';
        split(rowBuff, DL, &m_fields);
        while (fgets(rowBuff, MAX_ROW_SZ, (FILE *)fp))
        {
            rowBuff[strcspn(rowBuff, "\n")] = '\0';
            Add(rowBuff);
        }
    }
    fclose(fp);
}
CSVList::prows CSVList::Filter(const filter &filter, CSVList::prows &rows)
{
    CSVList::prows newProws;
    switch (filter.operand)
    {
    case filterOperand::EqualTo:
        for (auto &pcsv : rows)
        {
            auto &csv = *pcsv;
            if (*csv[filter.lhs] == filter.rhs)
            {
                newProws.push_back(&csv);
            }
        }
        break;
    default:
        break;
    }
    return newProws;
}

CSVList::prows &CSVList::Filter(const filter &filter, CSVList::rows &rows)
{
    switch (filter.operand)
    {
    case filterOperand::EqualTo:
        for (auto &csv : rows)
        {
            if (*csv[filter.lhs] == filter.rhs)
            {
                m_filteredList.push_back(&csv);
            }
        }
        break;
    default:
        break;
    }
    return m_filteredList;
}

CSVList::prows &CSVList::Filter(const std::vector<filter> &filters)
{
    bool init = false;
    m_filteredList.clear();
    for (auto &fltr : filters)
    {
        if (init)
        {
            m_filteredList = Filter(fltr, m_filteredList);
        }
        else
        {
            init = true;
            Filter(fltr, m_rows);
        }
    }
    return m_filteredList;
}
