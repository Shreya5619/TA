#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<msclr\marshal_cppstd.h>
#include "dept.h"
#include<algorithm>
namespace timetablearchitect {
	using namespace std;
	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for addsub
	/// </summary>
	public ref class addsub : public System::Windows::Forms::Form
	{
	public:

		timetablearchitect::dept^ dept = gcnew timetablearchitect::dept;
		addsub(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		std::string replacewhitespace(std::string text)
		{
			std::replace(text.begin(), text.end(), ' ', '_');
			return text;
		}
		void csvgen(System::String^ filePath)
		{
		
			std::ofstream outputFile;
			outputFile.open((msclr::interop::marshal_as<std::string>(filePath)),ios::app);	
			if (outputFile.is_open())
			{
				System::String^ name = textBox1->Text->ToString();
				std::string Name = replacewhitespace(dept->converter(name));
				outputFile << Name << ",";
				{if (radioButton1->Checked)
				{
					System::String^ ele = textBox2->Text->ToString();
					std::string Ele =replacewhitespace( dept->converter(ele));
					outputFile << Ele << ",";
						String^ FilePath = "Elective.csv";
						csvelective(FilePath);
				}
				else if (radioButton2->Checked)
				{
					outputFile << "0,";
				}}
				{if (radioButton3->Checked)
				{
					outputFile << "1,";
					{
						String^ filepath = "Labo.csv";
						csvlab(filepath);
					}
			}
				else
				{
					outputFile << "0,";
				}}
				System::String^ credits = numericUpDown1->Text->ToString();
				std::string Credits = dept->converter(credits);
				outputFile << Credits << ",";
				System::String^ noofhours = numericUpDown2->Text->ToString();
				std::string Noofhours = dept->converter(noofhours);
				outputFile << Noofhours << ",";
				System::String^ bfactor = numericUpDown3->Text->ToString();
				std::string Bfactor = dept->converter(bfactor);
				outputFile << Bfactor << ",";
				//code to add roomlist
				outputFile << "[";
				bool x = true;
				for (int i = 0; i < checkedListBox1->CheckedItems->Count; ++i) {
					String^ value = checkedListBox1->CheckedItems[i]->ToString();
					std::string Value = dept->converter(value);
					outputFile << Value;
					x = false;
					if (i < checkedListBox1->CheckedItems->Count - 1) {
						outputFile << ",";// Add a comma after each value, except the last one
					}
				}
				if (x)
				{
					outputFile << "0";
				}
				outputFile << "]\n";


				//code to add rank
				outputFile.close();
			}
		}
		vector<vector<string>> ReadCSVFile(const string& filename) {
			ifstream file(filename);
			vector<vector<string>> data;
			string line;

			while (getline(file, line)) {
				stringstream lineStream(line);
				vector<string> row;
				string cell;

				while (getline(lineStream, cell, ',')) {
					row.push_back(cell);
				}

				data.push_back(row);
			}
			file.close();
			return data;
		}
		void DisplayCSVInComboBox(const string& filename, ListBox^ ListBox) {
			vector<vector<string>> data = ReadCSVFile(filename);

			for (const auto& row : data) {
				if (!row.empty()) {
					// Display only the first word before the comma
					String^ firstWord = msclr::interop::marshal_as<String^>(row[0]);
					ListBox->Items->Add(firstWord);
				}
			}
		}
		void change(Button^ button)
		{
			if (button->Text == "free") {
				button->Text = "occupied";
			}
			else {
				button->Text = "free";
			}

		}
		void DisplayCSVInTextBox(String^ filePath, TextBox^ textBox)
		{
			try
			{
				StreamReader^ reader = gcnew StreamReader(filePath);
				String^ fileContent = reader->ReadToEnd(); // Read the entire file content

				// Set the text box text to display the CSV content
				textBox->Text = fileContent;

				reader->Close(); // Close the StreamReader when done
			}
			catch (Exception^ e)
			{
				// Handle any exceptions that might occur while reading the file
				textBox->Text = "Error reading the file: " + e->Message;
			}
		}
		void csvelective(System::String^ filePath)
		{

			std::ofstream outputFile;
			outputFile.open((msclr::interop::marshal_as<std::string>(filePath)), ios::app);
			{
				System::String^ name = textBox2->Text->ToString();
				std::string Name = replacewhitespace(dept->converter(name));
				outputFile << Name << ",";
				System::String^ elename = textBox1->Text->ToString();
				std::string eleName = replacewhitespace(dept->converter(elename));
				outputFile << eleName << ",";
				for (int i = 0; i < dataGridView1->RowCount-1; ++i)
				{
					if (dataGridView1->Rows[i]->Cells[0]->Value != nullptr)
					{
						System::String^ cellvalue = dataGridView1->Rows[i]->Cells[0]->Value->ToString();
						std::string CellValue = dept->converter(cellvalue);
						outputFile << CellValue<<",";
					}

				}outputFile << "\n";
			}outputFile.close();
		}
		void csvlab(System::String^ filePath)
		{

			std::ofstream outputFile;
			outputFile.open((msclr::interop::marshal_as<std::string>(filePath)), ios::app);
			{
				System::String^ name = textBox1->Text->ToString();
				std::string Name = replacewhitespace(dept->converter(name));
				outputFile << Name << ",";
				if (dataGridView3->Rows[0]->Cells[0]->Value != nullptr)
					outputFile << dept->converter(dataGridView3->Rows[0]->Cells[0]->Value->ToString());
				for (int i = 1; i < dataGridView3->RowCount; ++i)
				{

					if (dataGridView3->Rows[i]->Cells[0]->Value != nullptr)
					{
						System::String^ cellvalue = dataGridView3->Rows[i]->Cells[0]->Value->ToString();
						std::string CellValue = dept->converter(cellvalue);
						outputFile << ","<<CellValue;


					}
				}

			
				outputFile << "\n";
			}outputFile.close();
		}
		System::Data::DataTable^ CreateDataTableFromCSV1(const std::string filePath) {
			System::Data::DataTable^ dataTable = gcnew System::Data::DataTable();
			dataTable->Columns->Add("teacherName");
			timetablearchitect::addsub^ addsub = gcnew timetablearchitect::addsub;
			vector<vector<string>> data = addsub->ReadCSVFile(filePath);
			for (const auto& row : data) {
				if (!row.empty()) {
					// Display only the first word before the comma
					String^ teacherName = msclr::interop::marshal_as<String^>(row[0]);
					dataTable->Rows->Add(teacherName);
				}
			}
			return dataTable;
		}
		System::Data::DataTable^ CreateDataTableFromCSV2(const std::string filePath) {
			System::Data::DataTable^ dataTable = gcnew System::Data::DataTable();
			dataTable->Columns->Add("teacher_Name");
			timetablearchitect::addsub^ addsub = gcnew timetablearchitect::addsub;
			vector<vector<string>> data = addsub->ReadCSVFile(filePath);
			for (const auto& row : data) {
				if (!row.empty()) {
					// Display only the first word before the comma
					String^ teacher_Name = msclr::interop::marshal_as<String^>(row[0]);
					dataTable->Rows->Add(teacher_Name);
				}
			}
			return dataTable;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~addsub()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label4;


	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::RadioButton^ radioButton4;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown2;

	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown3;
	private: System::Windows::Forms::ListBox^ listBox2;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
private: System::Windows::Forms::TextBox^ textBox3;
private: System::Windows::Forms::Button^ button1;
private: System::Windows::Forms::DataGridView^ dataGridView1;

private: System::Windows::Forms::Panel^ panel1;
private: System::Windows::Forms::Label^ label5;

private: System::Windows::Forms::Label^ label11;
private: System::Windows::Forms::DataGridView^ dataGridView3;

private: System::Windows::Forms::Button^ button2;
private: System::Windows::Forms::CheckedListBox^ checkedListBox1;
private: System::Windows::Forms::Button^ button3;


private: System::Windows::Forms::DataGridViewComboBoxColumn^ teacherName;
private: System::Windows::Forms::DataGridViewButtonColumn^ deletecolumn;
private: System::Windows::Forms::DataGridViewComboBoxColumn^ teacher_Name;
private: System::Windows::Forms::DataGridViewButtonColumn^ Deletec;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->teacherName = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->deletecolumn = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->dataGridView3 = (gcnew System::Windows::Forms::DataGridView());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->teacher_Name = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->Deletec = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(103, 111);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(482, 26);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(99, 64);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(104, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"subject name";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(14, 11);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(62, 24);
			this->radioButton1->TabIndex = 2;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Yes";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &addsub::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(220, 11);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(54, 24);
			this->radioButton2->TabIndex = 3;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"No";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &addsub::radioButton2_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(99, 188);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(122, 20);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Is it an elective\?";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(99, 326);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(126, 20);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Name of elective";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(104, 376);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(482, 26);
			this->textBox2->TabIndex = 6;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(37, 682);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(81, 20);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Is it a lab\?";
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(33, 9);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(62, 24);
			this->radioButton3->TabIndex = 10;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Yes";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &addsub::radioButton3_CheckedChanged);
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(170, 9);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(54, 24);
			this->radioButton4->TabIndex = 11;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"No";
			this->radioButton4->UseVisualStyleBackColor = true;
			this->radioButton4->CheckedChanged += gcnew System::EventHandler(this, &addsub::radioButton4_CheckedChanged);
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(3, 1115);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(170, 26);
			this->numericUpDown1->TabIndex = 12;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(-1, 1164);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(195, 20);
			this->label6->TabIndex = 13;
			this->label6->Text = L"number of hours per credit";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(19, 1077);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(98, 20);
			this->label7->TabIndex = 14;
			this->label7->Text = L"No of credits";
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(3, 1209);
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(170, 26);
			this->numericUpDown2->TabIndex = 15;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 1272);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(205, 20);
			this->label8->TabIndex = 17;
			this->label8->Text = L"Rooms to be used(optional)";
			this->label8->Click += gcnew System::EventHandler(this, &addsub::label8_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(19, 1603);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(59, 20);
			this->label9->TabIndex = 18;
			this->label9->Text = L"bfactor";
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->DecimalPlaces = 2;
			this->numericUpDown3->Location = System::Drawing::Point(14, 1645);
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(170, 26);
			this->numericUpDown3->TabIndex = 19;
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->ItemHeight = 20;
			this->listBox2->Location = System::Drawing::Point(23, 1747);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(120, 24);
			this->listBox2->TabIndex = 20;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(3, 1688);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(133, 20);
			this->label10->TabIndex = 21;
			this->label10->Text = L" Preffered timings";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Location = System::Drawing::Point(23, 223);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(326, 60);
			this->groupBox1->TabIndex = 22;
			this->groupBox1->TabStop = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->radioButton4);
			this->groupBox2->Controls->Add(this->radioButton3);
			this->groupBox2->Location = System::Drawing::Point(23, 719);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(265, 39);
			this->groupBox2->TabIndex = 23;
			this->groupBox2->TabStop = false;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(547, 215);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(347, 117);
			this->textBox3->TabIndex = 24;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(372, 1839);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(116, 51);
			this->button1->TabIndex = 25;
			this->button1->Text = L"Save";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &addsub::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->teacherName,
					this->deletecolumn
			});
			this->dataGridView1->Location = System::Drawing::Point(37, 446);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 62;
			this->dataGridView1->RowTemplate->Height = 28;
			this->dataGridView1->Size = System::Drawing::Size(454, 207);
			this->dataGridView1->TabIndex = 26;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &addsub::dataGridView1_CellContentClick);
			// 
			// teacherName
			// 
			this->teacherName->HeaderText = L"Teacher Name";
			this->teacherName->MinimumWidth = 8;
			this->teacherName->Name = L"teacherName";
			this->teacherName->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->teacherName->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
			this->teacherName->Width = 200;
			// 
			// deletecolumn
			// 
			this->deletecolumn->HeaderText = L"Delete ";
			this->deletecolumn->MinimumWidth = 8;
			this->deletecolumn->Name = L"deletecolumn";
			this->deletecolumn->ReadOnly = true;
			this->deletecolumn->Text = L"Delete";
			this->deletecolumn->UseColumnTextForButtonValue = true;
			this->deletecolumn->Width = 150;
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->BackColor = System::Drawing::Color::Transparent;
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->checkedListBox1);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->label11);
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Controls->Add(this->dataGridView3);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->dataGridView1);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->listBox2);
			this->panel1->Controls->Add(this->groupBox2);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label10);
			this->panel1->Controls->Add(this->numericUpDown3);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Controls->Add(this->numericUpDown2);
			this->panel1->Controls->Add(this->numericUpDown1);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->label8);
			this->panel1->Controls->Add(this->label9);
			this->panel1->Location = System::Drawing::Point(66, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(798, 2000);
			this->panel1->TabIndex = 27;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &addsub::panel1_Paint);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(519, 1841);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(116, 51);
			this->button3->TabIndex = 34;
			this->button3->Text = L"Add";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &addsub::button3_Click);
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Location = System::Drawing::Point(22, 1327);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(224, 234);
			this->checkedListBox1->TabIndex = 33;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(679, 1842);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(116, 51);
			this->button2->TabIndex = 32;
			this->button2->Text = L"Back";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &addsub::button2_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(34, 788);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(246, 20);
			this->label11->TabIndex = 31;
			this->label11->Text = L"Teachers handling the lab subject";
			// 
			// dataGridView3
			// 
			this->dataGridView3->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView3->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->teacher_Name,
					this->Deletec
			});
			this->dataGridView3->Location = System::Drawing::Point(23, 822);
			this->dataGridView3->Name = L"dataGridView3";
			this->dataGridView3->RowHeadersWidth = 62;
			this->dataGridView3->RowTemplate->Height = 28;
			this->dataGridView3->Size = System::Drawing::Size(435, 207);
			this->dataGridView3->TabIndex = 30;
			this->dataGridView3->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &addsub::dataGridView3_CellContentClick);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(37, 408);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(278, 20);
			this->label5->TabIndex = 28;
			this->label5->Text = L"Teachers handling the elective subject";
			// 
			// teacher_Name
			// 
			this->teacher_Name->HeaderText = L"Teacher Name";
			this->teacher_Name->MinimumWidth = 8;
			this->teacher_Name->Name = L"teacher_Name";
			this->teacher_Name->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->teacher_Name->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
			this->teacher_Name->Width = 200;
			// 
			// Deletec
			// 
			this->Deletec->HeaderText = L"Delete";
			this->Deletec->MinimumWidth = 8;
			this->Deletec->Name = L"Deletec";
			this->Deletec->ReadOnly = true;
			this->Deletec->Text = L"Delete";
			this->Deletec->UseColumnTextForButtonValue = true;
			this->Deletec->Width = 150;
			// 
			// addsub
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1062, 1050);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->panel1);
			this->Name = L"addsub";
			this->Text = L"addsub";
			this->Load += gcnew System::EventHandler(this, &addsub::addsub_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void addsub_Load(System::Object^ sender, System::EventArgs^ e) {
		const std::string filePath = "building.csv";
		DisplayCSVInComboBox(filePath, checkedListBox1);
		const std::string fileName = "teacher_file.csv";
		teacherName->DataSource = CreateDataTableFromCSV1(fileName);
		teacherName->DisplayMember = "teacherName"; // Update to the correct column name
		teacherName->ValueMember = "teacherName";
		teacher_Name->DataSource = CreateDataTableFromCSV2(fileName);
		teacher_Name->DisplayMember = "teacher_Name"; // Update to the correct column name
		teacher_Name->ValueMember = "teacher_Name";
	}
private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (radioButton2->Checked)
	{
		textBox2->ReadOnly = radioButton2->Checked;
		textBox2->Clear();
		textBox2->Cursor = Cursors::No;
		dataGridView1->Rows->Clear();
		dataGridView1->Cursor = Cursors::No;
	}
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ filePath = "subject_file.csv";
	csvgen(filePath);
	DisplayCSVInTextBox(filePath, textBox3);

}
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (radioButton1->Checked)
		{
			textBox2->ReadOnly = !radioButton1->Checked;
			textBox2->Clear();
			dataGridView1->Cursor = Cursors::Arrow;
			textBox2->Cursor = Cursors::Arrow;
		}
	}
private: System::Void label8_Click(System::Object^ sender, System::EventArgs^ e) {
}
	private: System::Void radioButton4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		dataGridView3->Rows->Clear();
		dataGridView3->Cursor = Cursors::No;
	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	Form::Close();
}
private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	dataGridView3->Cursor = Cursors::Arrow;
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	textBox1->Clear();
	textBox2->Clear();
	radioButton1->Checked = false;
	radioButton2->Checked = false;
	radioButton3->Checked = false;
	radioButton4->Checked = false;
	dataGridView1->Rows->Clear();
	dataGridView3->Rows->Clear();
	numericUpDown1->Value = 0;
	numericUpDown2->Value = 0;
	numericUpDown3->Value = 0;
	for (int i = 0; i < checkedListBox1->Items->Count; i++) {
		checkedListBox1->SetItemChecked(i, false);
	}
}
private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
}
private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	try
	{
		if (e->ColumnIndex == dataGridView1->Columns["deletecolumn"]->Index && e->RowIndex >= 0)
		{
			// Retrieve the index of the row to delete
			int rowIndexToDelete = e->RowIndex;

			// Remove the row from the DataGridView
			dataGridView1->Rows->RemoveAt(rowIndexToDelete);
		}
	}
	catch (...)
	{

	}
}
private: System::Void dataGridView3_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	try
	{
		if (e->ColumnIndex == dataGridView3->Columns["Deletec"]->Index && e->RowIndex >= 0)
		{
			// Retrieve the index of the row to delete
			int rowIndexToDelete = e->RowIndex;

			// Remove the row from the DataGridView
			dataGridView3->Rows->RemoveAt(rowIndexToDelete);
		}
	}
	catch (...)
	{

	}
}

};
}
