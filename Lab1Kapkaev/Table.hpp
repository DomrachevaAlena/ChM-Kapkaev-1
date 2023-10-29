#pragma once
#include <ios>
#include <iomanip>
#include <iostream>

#include <vector>
#include <string>

class Table
{
	std::vector<std::string> columnNames;
	std::vector<std::vector<double>> columns;
public:
	Table() {}

	Table(const std::vector<std::string>& rowNames)
	{
		this->columnNames = rowNames;
		columns = std::vector<std::vector<double>>(rowNames.size());
	}

	Table(size_t vSize)
	{
		columnNames.push_back("Xi");

		if (vSize == 1)
		{
			columnNames.push_back("Vi");
			columnNames.push_back("V2i");
			columnNames.push_back("Vi-V2i");
			columnNames.push_back("OLP");
		}
		else
		{
			for (size_t i = 0; i < vSize; i++)
			{
				columnNames.push_back("Vi" + std::to_string(i + 1));
				columnNames.push_back("V2i" + std::to_string(i + 1));
				columnNames.push_back("Vi" + std::to_string(i + 1) + "-" + "V2i" + std::to_string(i + 1));
				columnNames.push_back("OLP" + std::to_string(i + 1));
			}
		}

		columnNames.push_back("h");
		columnNames.push_back("C1");
		columnNames.push_back("C2");

		columns = std::vector<std::vector<double>>(columnNames.size());
	}

	void addRow(const std::vector<double>& row)
	{
		for (int i = 0; i < columns.size(); i++)
			columns[i].push_back(row[i]);
	}

	void addRow(double x,const std::vector<double> &v, const std::vector<double> &v2, double h, double C1, double C2)
	{
		columns[0].push_back(x);

		int i = 1;
		for (int j=0; j < v.size(); i++,j++)
			columns[i].push_back(v[j]);

		for (int j = 0; j < v.size(); i++, j++)
			columns[i].push_back(v2[j]);

		for (int j = 0; j < v.size(); i++, j++)
			columns[i].push_back(v[j] - v2[j]);

		for (int j = 0; j < v.size(); i++, j++)
			columns[i].push_back((v[j] - v2[j]) / 15.0);

		columns[i].push_back(h);
		columns[++i].push_back(C1);
		columns[++i].push_back(C2);
	}

	void addColumn(std::string columnName, const std::vector<double> &values)
	{
		columnNames.push_back(columnName);
		columns.push_back(values);
	}

	void printTable()
	{
		for (int i = 0; i < columnNames.size(); i++)
			std::cout << std::setw(15) << columnNames[i] << "|";

		std::cout << std::endl;

		for (int i = 0; i < columns[0].size(); i++)
		{
			for (int j = 0; j < columns.size(); j++)
				std::cout << std::internal << std::setw(15) << columns[j][i] << ";";
			std::cout << std::endl;
		}
	}

	~Table();
};