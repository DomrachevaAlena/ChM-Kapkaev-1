#pragma once
#include <ios>
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>
#include <string>

class MyTable
{
	std::vector<std::string> columnNames;
	std::vector<std::vector<double>> columns;
public:
	MyTable() {}

	MyTable(const std::vector<std::string>& rowNames)
	{
		this->columnNames = rowNames;
		columns = std::vector<std::vector<double>>(rowNames.size());
	}

	MyTable(size_t vSize)
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
				columnNames.push_back("Vi" + std::to_string(i + 1));
			for (size_t i = 0; i < vSize; i++)
				columnNames.push_back("V2i" + std::to_string(i + 1));

			for (size_t i = 0; i < vSize; i++)
				columnNames.push_back("Vi" + std::to_string(i + 1) + "-" + "V2i" + std::to_string(i + 1));

			for (size_t i = 0; i < vSize; i++)
				columnNames.push_back("OLP" + std::to_string(i + 1));
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
			columns[i].push_back(16.0*(v2[j] - v[j]) / 15.0);

		columns[i].push_back(h);
		columns[++i].push_back(C1);
		columns[++i].push_back(C2);
	}

	void addColumn(std::string columnName,std::vector<double> values)
	{
		columnNames.push_back(columnName);
		columns.push_back(values);
	}

	void printTable()
	{
		size_t width = 13;

		for (int i = 0; i < columnNames.size(); i++)
			std::cout << std::setw(width) << columnNames[i] << "|";

		std::cout << std::endl;

		for (int i = 0; i < columns[0].size(); i++)
		{
			for (int j = 0; j < columns.size(); j++)
				std::cout << std::right << std::setw(width) << columns[j][i] << "|";
			std::cout << std::endl;
		}
	}

	void saveToTXT(std::string outPath = "defaulOut.txt")
	{
		std::ofstream out(outPath);

		size_t width = 13;

		if (out.is_open())
		{
			for (int i = 0; i < columnNames.size(); i++)
				out << std::setw(width) << columnNames[i] << "|";

			out << std::endl;

			for (int i = 0; i < columns[0].size(); i++)
			{
				for (int j = 0; j < columns.size(); j++)
					out << std::right << std::setw(width) << columns[j][i] << "|";
				out << std::endl;
			}
		}
		out.close();
	}

	std::vector<double> getColumn(std::string columnName)
	{
		size_t columnInd;

		for (size_t i = 0; i < columnNames.size(); i++)
			if (columnNames[i] == columnName)
				columnInd = i;

		return columns[columnInd];
	}

	~MyTable();
};