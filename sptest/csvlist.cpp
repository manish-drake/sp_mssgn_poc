#include "csvlist.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

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
    char workingCopy[MAX_ROW_SZ] = {0};
    strcpy(workingCopy, str);
    char *ptr = strtok(workingCopy, delimitter);
    while (ptr)
    {
        collection->push_back(ptr);
        ptr = strtok(nullptr, delimitter);
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

CSVList::prows &CSVList::Filter(const filter &filter)
{
    switch (filter.operand)
    {
    case filterOperand::EqualTo:
        for (auto &csv : m_rows)
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
    m_filteredList.clear();
    for (auto &fltr : filters)
    {
        Filter(fltr);
    }
    return m_filteredList;
}