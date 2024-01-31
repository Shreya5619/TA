#pragma once
#include "addname.h"
#include"addsub.h"
#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<msclr\marshal_cppstd.h>
#include<list>
#define days 6
#define periods 6
#include"Header.h"
#include<Windows.h>
#include <vcclr.h>
namespace timetablearchitect {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for addclass
	/// </summary>
	public ref class addclass : public System::Windows::Forms::Form
	{
	public:
		addclass(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		std::string returnLine(std::string name, std::string path) {
			std::fstream file(path);
			for (int i = 0; i < 1000; i++) {
				std::string line;
				if (file.eof()) {
					break;
				}
				file >> line;
				int j;
				for (j = 0; j < name.size(); j++) {
					if (name[j] != line[j]) {
						goto a;
					}
				}
				return line;
			a:
				continue;
			}
			file.close();
			return "not found";
		}
		System::Data::DataTable^ CreateDataTableFromCSV1(const std::string filePath) {
			System::Data::DataTable^ dataTable = gcnew System::Data::DataTable();
			dataTable->Columns->Add("subject");
			timetablearchitect::addsub^ addsub = gcnew timetablearchitect::addsub;
			vector<vector<string>> data = addsub->ReadCSVFile(filePath);
			for (const auto& row : data) {
				if (!row.empty()) {
					// Display only the first word before the comma
					String^ subject = msclr::interop::marshal_as<String^>(row[0]);
					dataTable->Rows->Add(subject);
				}
			}
			return dataTable;
		}
		System::Data::DataTable^ CreateDataTableFromCSV2(const std::string filePath) {
			System::Data::DataTable^ dataTable = gcnew System::Data::DataTable();
			dataTable->Columns->Add("Teacher");
			timetablearchitect::addsub^ addsub = gcnew timetablearchitect::addsub;
			vector<vector<string>> data = addsub->ReadCSVFile(filePath);
			for (const auto& row : data) {
				if (!row.empty()) {
					// Display only the first word before the comma
					String^ Subject = msclr::interop::marshal_as<String^>(row[0]);
					dataTable->Rows->Add(Subject);
				}
			}
			return dataTable;
		}
		System::Data::DataTable^ CreateDataTableFromCSV3(const std::string filePath) {
			System::Data::DataTable^ dataTable = gcnew System::Data::DataTable();
			dataTable->Columns->Add("ElectiveSub");
			timetablearchitect::addsub^ addsub = gcnew timetablearchitect::addsub;
			vector<vector<string>> data = addsub->ReadCSVFile(filePath);
			for (const auto& row : data) {
				if (!row.empty()) {
					// Display only the first word before the comma
					String^ ElectiveSub = msclr::interop::marshal_as<String^>(row[0]);
					dataTable->Rows->Add(ElectiveSub);
				}
			}
			return dataTable;
		}
		System::Data::DataTable^ CreateDataTableFromCSV4(const std::string filePath) {
			System::Data::DataTable^ dataTable = gcnew System::Data::DataTable();
			dataTable->Columns->Add("LabSub");
			timetablearchitect::addsub^ addsub = gcnew timetablearchitect::addsub;
			vector<vector<string>> data = addsub->ReadCSVFile(filePath);
			for (const auto& row : data) {
				if (!row.empty()) {
					// Display only the first word before the comma
					String^ LabSub = msclr::interop::marshal_as<String^>(row[0]);
					dataTable->Rows->Add(LabSub);
				}
			}
			return dataTable;
		}
		std::string replacewhitespace(std::string text)
		{
			std::replace(text.begin(), text.end(), ' ', '_');
			return text;
		}

		void duplicateCSV(const string filepath, const string originalfile) {
			try
			{
				std::fstream outputFile;
				outputFile.open(filepath);
				if (!outputFile.is_open()) {
					ofstream outFile;
					outFile.open(filepath);
					std::fstream inputFile;
					inputFile.open(originalfile);
					string inp;
					if (inputFile.is_open())
					{
						while (inputFile >> inp) {
							outFile << inp << endl;

						}
					}
					inputFile.close();
				}
				outputFile.close();

			}
			catch (...)
			{

			}
		}
		void over(String^ original, String^ duplicate)
		{
			try
			{
				StreamReader^ reader = gcnew StreamReader(duplicate);
				String^ fileContent = reader->ReadToEnd();
				StreamWriter^ writer = gcnew StreamWriter(original);
				writer->Write(fileContent);

				reader->Close();
				writer->Close();
			}
			catch (...)
			{

			}
		}


		void convertteacherstovector(const string filename, section& t)
		{
			std::fstream outputFile;
			outputFile.open(filename);
			{ string line;
			while (outputFile >> line)
			{
				teacher obj;
				obj.readData(line);
				t.allTeachers.push_back(obj);

			}
			}
		}
		void convertroomstovector(const string filename, section& t)
		{
			std::fstream outputFile;
			outputFile.open(filename);
			{ string line;
			while (outputFile >> line)
			{
				room obj;
				obj.readData(line);
				t.allRooms.push_back(obj);
			}
			}
		}

		void convertroomstocsv(const string filename, section& t)
		{
			std::fstream outputfile;
			outputfile.open(filename);
			for (auto& value : t.allRooms)
				outputfile << value.convertToString() << endl;
			outputfile.close();

		}
		void convertteachertocsv(const string filename, section& t)
		{
			std::fstream outputfile;
			outputfile.open(filename);
			for (int i = 0; i < t.allTeachers.size(); i++)
			{
				outputfile << t.allTeachers[i].convertToString() << endl;
			}
			outputfile.close();
		}


		void labcreate(const string filename, section& t)
		{
			timetablearchitect::addsub^ addsub = gcnew timetablearchitect::addsub;
			vector<vector<string>>abc = addsub->ReadCSVFile(filename);
			for (int i = 0; i < dataGridView3->RowCount; ++i)
			{
				if (dataGridView3->Rows[i]->Cells[0]->Value != nullptr)
				{
					System::String^ cellvalue = dataGridView3->Rows[i]->Cells[0]->Value->ToString();
					std::string CellValue = msclr::interop::marshal_as<string>(cellvalue);
					teacher a[10];
					/*int j, b = 0;
					for (j = 0; j < abc.size(); j++)
					{


						
							if (CellValue == (abc[j][0]))
							{

								for (int k = 1; k < abc[j].size(); k++) {

									a[k - 1] = t.returnTeacher(abc[j][k]);
									b++;
								}


							}
					}
					string filePath = "subject_file.csv";

					::subject subj;

					subj.readData(returnLine(CellValue, filePath));
					textBox10->Text = msclr::interop::marshal_as<String^>(to_string(b));
					vector<teacher> temp;
					for (int q = 0; q < b; q++) {
						temp.push_back(a[q]);
					}
					t.labSubjects.push_back(subj);
					textBox10->Text = "pushed sub";
					t.labTeachers.push_back(temp);
					textBox10->Text = "pushed labs";
					textBox10->Text = msclr::interop::marshal_as<String^>(t.returnRoom(subj.rooms[0]).name);
					t.addLab(a, b, subj, 2);*/


				}
				
			}
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~addclass()
		{
			if (components)
			{
				delete components;
			}
		}
private: System::Windows::Forms::Label^ label1;
protected:
private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::MaskedTextBox^ maskedTextBox2;
private: System::Windows::Forms::ComboBox^ comboBox1;
private: System::Windows::Forms::Label^ label2;
private: System::Windows::Forms::MaskedTextBox^ maskedTextBox1;
private: System::Windows::Forms::Label^ label4;
private: System::Windows::Forms::DataGridView^ dataGridView2;
private: System::Windows::Forms::DataGridViewComboBoxColumn^ ElectiveSub;
private: System::Windows::Forms::DataGridViewButtonColumn^ deletec;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::DataGridView^ dataGridView1;
private: System::Windows::Forms::DataGridViewComboBoxColumn^ subject;
private: System::Windows::Forms::DataGridViewComboBoxColumn^ Teacher;
private: System::Windows::Forms::DataGridViewButtonColumn^ deletecolumn;
private: System::Windows::Forms::CheckedListBox^ checkedListBox1;
private: System::Windows::Forms::TextBox^ textBox10;
private: System::Windows::Forms::Label^ label7;
private: System::Windows::Forms::TextBox^ textBox2;
private: System::Windows::Forms::Button^ button4;
private: System::Windows::Forms::Button^ button3;
private: System::Windows::Forms::Button^ button1;
private: System::Windows::Forms::DataGridView^ dataGridView3;
private: System::Windows::Forms::DataGridViewComboBoxColumn^ LabSub;
private: System::Windows::Forms::DataGridViewButtonColumn^ Deleteco;
private: System::Windows::Forms::Button^ button2;

	protected:





























































































































	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle10 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle13 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle12 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle11 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::Panel^ panel1;
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->maskedTextBox2 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->maskedTextBox1 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->deletec = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->ElectiveSub = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->deletecolumn = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->Teacher = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->subject = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView3 = (gcnew System::Windows::Forms::DataGridView());
			this->Deleteco = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->LabSub = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			this->button2 = (gcnew System::Windows::Forms::Button());
			panel1 = (gcnew System::Windows::Forms::Panel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->BeginInit();
			panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(331, 94);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(94, 32);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Section";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(335, 221);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(90, 32);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Branch";
			// 
			// maskedTextBox2
			// 
			this->maskedTextBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)), static_cast<System::Int32>(static_cast<System::Byte>(211)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->maskedTextBox2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->maskedTextBox2->Location = System::Drawing::Point(337, 155);
			this->maskedTextBox2->Mask = L"A";
			this->maskedTextBox2->Name = L"maskedTextBox2";
			this->maskedTextBox2->Size = System::Drawing::Size(434, 39);
			this->maskedTextBox2->TabIndex = 8;
			this->maskedTextBox2->MaskInputRejected += gcnew System::Windows::Forms::MaskInputRejectedEventHandler(this, &addclass::maskedTextBox2_MaskInputRejected);
			// 
			// comboBox1
			// 
			this->comboBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)), static_cast<System::Int32>(static_cast<System::Byte>(211)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(341, 279);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(269, 40);
			this->comboBox1->TabIndex = 9;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(335, 351);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(283, 32);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Batch(year of admission)";
			this->label2->Click += gcnew System::EventHandler(this, &addclass::label2_Click);
			// 
			// maskedTextBox1
			// 
			this->maskedTextBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)), static_cast<System::Int32>(static_cast<System::Byte>(211)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->maskedTextBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->maskedTextBox1->Location = System::Drawing::Point(341, 405);
			this->maskedTextBox1->Mask = L"0000";
			this->maskedTextBox1->Name = L"maskedTextBox1";
			this->maskedTextBox1->Size = System::Drawing::Size(401, 39);
			this->maskedTextBox1->TabIndex = 5;
			this->maskedTextBox1->ValidatingType = System::Int32::typeid;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(335, 468);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(654, 96);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Select the subjects taught and their corresponding teacher\r\n\r\n for non-elective a"
				L"nd non-lab subjects";
			// 
			// dataGridView2
			// 
			this->dataGridView2->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dataGridView2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->ElectiveSub,
					this->deletec
			});
			this->dataGridView2->Location = System::Drawing::Point(328, 895);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersWidth = 62;
			this->dataGridView2->RowTemplate->Height = 28;
			this->dataGridView2->Size = System::Drawing::Size(822, 170);
			this->dataGridView2->TabIndex = 29;
			// 
			// deletec
			// 
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::Color::Black;
			this->deletec->DefaultCellStyle = dataGridViewCellStyle2;
			this->deletec->HeaderText = L"Delete";
			this->deletec->MinimumWidth = 8;
			this->deletec->Name = L"deletec";
			this->deletec->ReadOnly = true;
			this->deletec->Text = L"Delete";
			this->deletec->UseColumnTextForButtonValue = true;
			this->deletec->Width = 150;
			// 
			// ElectiveSub
			// 
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::Color::Black;
			this->ElectiveSub->DefaultCellStyle = dataGridViewCellStyle1;
			this->ElectiveSub->HeaderText = L"subject";
			this->ElectiveSub->MinimumWidth = 8;
			this->ElectiveSub->Name = L"ElectiveSub";
			this->ElectiveSub->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->ElectiveSub->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
			this->ElectiveSub->Width = 150;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(331, 1086);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(147, 32);
			this->label6->TabIndex = 32;
			this->label6->Text = L"Lab subjects";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(322, 820);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(190, 32);
			this->label5->TabIndex = 31;
			this->label5->Text = L"Elective subjects";
			// 
			// dataGridView1
			// 
			this->dataGridView1->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dataGridView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dataGridView1->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::Sunken;
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle3;
			this->dataGridView1->ColumnHeadersHeight = 34;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->subject,
					this->Teacher, this->deletecolumn
			});
			this->dataGridView1->Cursor = System::Windows::Forms::Cursors::Default;
			dataGridViewCellStyle7->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle7->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle7->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle7->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle7->SelectionForeColor = System::Drawing::SystemColors::Desktop;
			dataGridViewCellStyle7->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle7;
			this->dataGridView1->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(245)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dataGridView1->Location = System::Drawing::Point(311, 604);
			this->dataGridView1->Name = L"dataGridView1";
			dataGridViewCellStyle8->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle8->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle8->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle8->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle8->SelectionForeColor = System::Drawing::SystemColors::Desktop;
			dataGridViewCellStyle8->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->RowHeadersDefaultCellStyle = dataGridViewCellStyle8;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidth = 62;
			dataGridViewCellStyle9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle9->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle9->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle9->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridView1->RowsDefaultCellStyle = dataGridViewCellStyle9;
			this->dataGridView1->RowTemplate->Height = 28;
			this->dataGridView1->Size = System::Drawing::Size(617, 176);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &addclass::dataGridView1_CellContentClick);
			// 
			// deletecolumn
			// 
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle6->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::Color::Black;
			this->deletecolumn->DefaultCellStyle = dataGridViewCellStyle6;
			this->deletecolumn->HeaderText = L"Delete";
			this->deletecolumn->MinimumWidth = 8;
			this->deletecolumn->Name = L"deletecolumn";
			this->deletecolumn->Text = L"Delete";
			this->deletecolumn->UseColumnTextForButtonValue = true;
			this->deletecolumn->Width = 150;
			// 
			// Teacher
			// 
			dataGridViewCellStyle5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle5->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::Color::Black;
			this->Teacher->DefaultCellStyle = dataGridViewCellStyle5;
			this->Teacher->HeaderText = L"Teacher";
			this->Teacher->MinimumWidth = 8;
			this->Teacher->Name = L"Teacher";
			this->Teacher->Width = 150;
			// 
			// subject
			// 
			dataGridViewCellStyle4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle4->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::Color::Black;
			this->subject->DefaultCellStyle = dataGridViewCellStyle4;
			this->subject->HeaderText = L"subject";
			this->subject->MinimumWidth = 8;
			this->subject->Name = L"subject";
			this->subject->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->subject->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
			this->subject->Width = 150;
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(245)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->checkedListBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->checkedListBox1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Location = System::Drawing::Point(337, 1430);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(287, 180);
			this->checkedListBox1->TabIndex = 33;
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(1267, 1687);
			this->textBox10->Multiline = true;
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(326, 91);
			this->textBox10->TabIndex = 28;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(331, 1352);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(169, 32);
			this->label7->TabIndex = 34;
			this->label7->Text = L"Default rooms";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(1124, -457);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(347, 117);
			this->textBox2->TabIndex = 25;
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)), static_cast<System::Int32>(static_cast<System::Byte>(211)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button4->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(845, 1614);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(147, 42);
			this->button4->TabIndex = 26;
			this->button4->Text = L"Generate";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &addclass::button4_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)), static_cast<System::Int32>(static_cast<System::Byte>(211)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(1018, 1614);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(104, 42);
			this->button3->TabIndex = 12;
			this->button3->Text = L"Save";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &addclass::button3_Click_1);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)), static_cast<System::Int32>(static_cast<System::Byte>(211)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(1160, 1614);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(132, 42);
			this->button1->TabIndex = 10;
			this->button1->Text = L"Add New";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &addclass::button3_Click);
			// 
			// dataGridView3
			// 
			this->dataGridView3->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dataGridView3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			dataGridViewCellStyle10->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle10->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle10->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle10->SelectionForeColor = System::Drawing::SystemColors::Desktop;
			dataGridViewCellStyle10->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView3->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle10;
			this->dataGridView3->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView3->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->LabSub,
					this->Deleteco
			});
			dataGridViewCellStyle13->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle13->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle13->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle13->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle13->SelectionForeColor = System::Drawing::SystemColors::Desktop;
			dataGridViewCellStyle13->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView3->DefaultCellStyle = dataGridViewCellStyle13;
			this->dataGridView3->Location = System::Drawing::Point(328, 1142);
			this->dataGridView3->Name = L"dataGridView3";
			this->dataGridView3->RowHeadersWidth = 62;
			this->dataGridView3->RowTemplate->Height = 28;
			this->dataGridView3->Size = System::Drawing::Size(964, 157);
			this->dataGridView3->TabIndex = 30;
			this->dataGridView3->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &addclass::dataGridView3_CellContentClick_1);
			// 
			// Deleteco
			// 
			dataGridViewCellStyle12->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle12->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle12->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle12->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle12->SelectionForeColor = System::Drawing::Color::Black;
			this->Deleteco->DefaultCellStyle = dataGridViewCellStyle12;
			this->Deleteco->HeaderText = L"Delete";
			this->Deleteco->MinimumWidth = 8;
			this->Deleteco->Name = L"Deleteco";
			this->Deleteco->ReadOnly = true;
			this->Deleteco->Text = L"Delete";
			this->Deleteco->UseColumnTextForButtonValue = true;
			this->Deleteco->Width = 150;
			// 
			// LabSub
			// 
			dataGridViewCellStyle11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle11->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle11->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			dataGridViewCellStyle11->SelectionForeColor = System::Drawing::Color::Black;
			this->LabSub->DefaultCellStyle = dataGridViewCellStyle11;
			this->LabSub->HeaderText = L"subject";
			this->LabSub->MinimumWidth = 8;
			this->LabSub->Name = L"LabSub";
			this->LabSub->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->LabSub->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Automatic;
			this->LabSub->Width = 150;
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(196)), static_cast<System::Int32>(static_cast<System::Byte>(211)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(1343, 1614);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(104, 42);
			this->button2->TabIndex = 35;
			this->button2->Text = L"Back";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &addclass::button2_Click);
			// 
			// panel1
			// 
			panel1->AutoScroll = true;
			panel1->Controls->Add(this->button2);
			panel1->Controls->Add(this->dataGridView3);
			panel1->Controls->Add(this->button1);
			panel1->Controls->Add(this->button3);
			panel1->Controls->Add(this->button4);
			panel1->Controls->Add(this->textBox2);
			panel1->Controls->Add(this->label7);
			panel1->Controls->Add(this->textBox10);
			panel1->Controls->Add(this->checkedListBox1);
			panel1->Controls->Add(this->dataGridView1);
			panel1->Controls->Add(this->label5);
			panel1->Controls->Add(this->label6);
			panel1->Controls->Add(this->dataGridView2);
			panel1->Controls->Add(this->label4);
			panel1->Controls->Add(this->maskedTextBox1);
			panel1->Controls->Add(this->label2);
			panel1->Controls->Add(this->comboBox1);
			panel1->Controls->Add(this->maskedTextBox2);
			panel1->Controls->Add(this->label3);
			panel1->Controls->Add(this->label1);
			panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			panel1->Location = System::Drawing::Point(0, 0);
			panel1->Name = L"panel1";
			panel1->Size = System::Drawing::Size(1898, 909);
			panel1->TabIndex = 17;
			panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &addclass::panel1_Paint);
			// 
			// addclass
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(245)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->ClientSize = System::Drawing::Size(1898, 909);
			this->Controls->Add(panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"addclass";
			this->ShowIcon = false;
			this->Text = L"addclass";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &addclass::addclass_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->EndInit();
			panel1->ResumeLayout(false);
			panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void addclass_Load(System::Object^ sender, System::EventArgs^ e) {
		const std::string filePath = "dept_file.csv";
		const std::string filepath = "building.csv";
		timetablearchitect::addsub^ addsub = gcnew timetablearchitect::addsub;
		addsub->DisplayCSVInComboBox(filepath, checkedListBox1);
		timetablearchitect::addname^ addname = gcnew timetablearchitect::addname;
		addname->DisplayCSVInComboBox(filePath, comboBox1);
		const std::string fileName = "subject_file.csv";
		const std::string Filename = "teacher_file.csv";
		subject->DataSource = CreateDataTableFromCSV1(fileName);
		subject->DisplayMember = "subject";
		subject->ValueMember = "subject";
		Teacher->DataSource = CreateDataTableFromCSV2(Filename);
		Teacher->DisplayMember = "Teacher";
		Teacher->ValueMember = "Teacher";
		ElectiveSub->DataSource = CreateDataTableFromCSV3(fileName);
		ElectiveSub->DisplayMember = "ElectiveSub";
		ElectiveSub->ValueMember = "ElectiveSub";
		LabSub->DataSource = CreateDataTableFromCSV4(fileName);
		LabSub->DisplayMember = "Labsub";
		LabSub->ValueMember = "LabSub";
		string originalFilePath = "building.csv";
		string duplicateFilePath = "buidingcopy.csv";
		duplicateCSV(duplicateFilePath, originalFilePath);
		string originalFilePath1 = "teacher_file.csv";
		string duplicateFilePath1 = "teachercopy.csv";
		duplicateCSV(duplicateFilePath1, originalFilePath1);
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void button3_Click_1(System::Object^ sender, System::EventArgs^ e) {


		timetablearchitect::addsub^ addsub = gcnew timetablearchitect::addsub;
		String^ sec = maskedTextBox1->Text->ToString();
		timetablearchitect::dept^ dept = gcnew timetablearchitect::dept;
		string Sec = dept->converter(sec);
		int secval;
		//Making class name
		if (Sec[0] > 'Z')
		{
			secval = Sec[0] - 'a';
		}
		else
			secval = Sec[0] - 'A';
		String^ branch = comboBox1->Text->ToString();
		string Branch = replacewhitespace(dept->converter(branch));
		int branchval = 0;
		for (int i = 0; i < Branch.size(); i++)
			if (Branch[i] > 'Z')
			{
				branchval = Branch[i] - 'a';
			}
			else
				branchval = Branch[i] - 'A';
		String^ year = maskedTextBox2->Text->ToString();
		string YEAR = dept->converter(year);
		int intyear = 0;
		for (int i = 0; i < YEAR.size(); i++) {
			intyear *= 10;
			intyear += YEAR[i] - '0';
		}
		int idClass = intyear * 10000 + branchval * 10 + secval;
		//reading teachers
		vector<teacher> teachers;
		for (int i = 0; i < dataGridView1->RowCount; ++i)
		{
			if (dataGridView1->Rows[i]->Cells[1]->Value != nullptr)
			{
				string file = "";
				string filePath = "teachercopy.csv";
				vector<vector<string>> data = addsub->ReadCSVFile(filePath);
				for (const auto& row : data)
				{
					if (!row.empty()) {
						// Display only the first word before the comma
						String^ teach = msclr::interop::marshal_as<String^>(row[0]);
						String^ s = dataGridView1->Rows[i]->Cells[1]->Value->ToString();
						if (s == teach)
						{
							for (int i = 0; i < row.size() - 1; i++)
								file += row[i] + ",";
							file += row[row.size() - 1];
						}
					}
				}

				teacher temp;
				temp.readData(file);
				teachers.push_back(temp);
			}
		}
		//reading subjects
		vector<::subject> subs;
		for (int i = 0; i < dataGridView1->RowCount; ++i)
		{
			if (dataGridView1->Rows[i]->Cells[0]->Value != nullptr)
			{
				string file = "";
				string filePath = "subject_file.csv";
				vector<vector<string>> data = addsub->ReadCSVFile(filePath);
				for (const auto& row : data)
				{
					if (!row.empty()) {
						// Display only the first word before the comma
						String^ subj = msclr::interop::marshal_as<String^>(row[0]);
						String^ s = dataGridView1->Rows[i]->Cells[0]->Value->ToString();
						if (s == subj)
						{
							for (int i = 0; i < row.size() - 1; i++)
								file += row[i] + ",";
							file += row[row.size() - 1];
						}
					}

				}

				::subject temp;
				temp.readData(file);
				subs.push_back(temp);
			}
		}

		for (int i = 0; i < dataGridView2->RowCount; ++i)
		{
			if (dataGridView2->Rows[i]->Cells[0]->Value != nullptr)
			{
				string file = "";
				string filePath = "subject_file.csv";
				vector<vector<string>> data = addsub->ReadCSVFile(filePath);
				for (const auto& row : data)
				{
					if (!row.empty()) {
						// Display only the first word before the comma
						String^ subj = msclr::interop::marshal_as<String^>(row[0]);
						String^ s = dataGridView2->Rows[i]->Cells[0]->Value->ToString();
						if (s == subj)
						{
							for (int i = 0; i < row.size() - 1; i++)
								file += row[i] + ",";
							file += row[row.size() - 1];
						}
					}

				}

				::subject temp;
				temp.readData(file);
				subs.push_back(temp);
			}
		}
		for (int i = 0; i < dataGridView3->RowCount; ++i)
		{
			if (dataGridView3->Rows[i]->Cells[0]->Value != nullptr)
			{
				string file = "";
				string filePath = "subject_file.csv";
				vector<vector<string>> data = addsub->ReadCSVFile(filePath);
				for (const auto& row : data)
				{
					if (!row.empty()) {
						// Display only the first word before the comma
						String^ subj = msclr::interop::marshal_as<String^>(row[0]);
						String^ s = dataGridView3->Rows[i]->Cells[0]->Value->ToString();
						if (s == subj)
						{
							for (int i = 0; i < row.size() - 1; i++)
								file += row[i] + ",";
							file += row[row.size() - 1];
						}
					}

				}

				::subject temp;
				temp.readData(file);
				subs.push_back(temp);
			}
		}
		vector <room> rooms;
		section obj;
		obj.name = idClass;
		for each (int checkedIndex in checkedListBox1->CheckedIndices)
		{
			String^ itemRoom = checkedListBox1->Items[checkedIndex]->ToString();
			string ItemRoom = dept->converter(itemRoom);
			string builds = "";
			string filepath = "buidingcopy.csv";
			vector<vector<string>> data = addsub->ReadCSVFile(filepath);
			for (const auto& row : data)
			{
				if (!row.empty())
				{
					if (ItemRoom == row[0])
					{
						obj.defaultRooms.push_back(row[0]);
						for (int i = 0; i < row.size() - 1; i++)
							builds += row[i] + ",";
						builds += row[row.size() - 1];
					}
				}
			}
			room temp;
			temp.readData(builds);
			rooms.push_back(temp);

		}

		string teache = "teachercopy.csv";
		string fileP = "buidingcopy.csv";
		std::fstream filePath(fileP);
		string line;
		if (filePath.is_open())
		{
			while (filePath >> line)
			{
				room temp;
				temp.readData(line);
				obj.allRooms.push_back(temp);
			}
		}
		filePath.close();
		std::fstream filePaths(teache);
		string lines;
		if (filePaths.is_open())
		{
			while (filePaths >> lines)
			{
				teacher temp;
				temp.readData(lines);
				obj.allTeachers.push_back(temp);
			}
		}
		filePaths.close();
		string filelist = "Labo.csv";
		labcreate(filelist, obj);
		for (int i = 0; i < teachers.size(); i++)
		{
			obj.addCore(teachers[i], subs[i]);
		}
		//convertroomstovector(FileP, obj);
		//convertroomstovector(teache, obj);
		obj.makeTIMETABLE();
		obj.storeTimeTable();
		string output = "";
		for (int k = 0; k < days; k++)
		{
			for (int l = 0; l < periods; l++)
			{
				output += obj.timeTable[k][l] + " , ";

			}
			output += "\n";

		}
		output += "\nteachers\n";
		for (int k = 0; k < days; k++)
		{
			for (int l = 0; l < periods; l++)
			{
				output += obj.teacherTable[k][l] + " , ";
			}
			output += "\n";
		}
		output += "\nroom\n";
		for (int k = 0; k < days; k++)
		{
			for (int l = 0; l < periods; l++)
			{
				output += obj.roomTable[k][l] + " , ";
			}
			output += "\n";
		}

		String^ Output = msclr::interop::marshal_as<String^>(output);
		textBox2->Text = Output;
		convertroomstocsv(fileP, obj);
		convertteachertocsv(teache, obj);

	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		maskedTextBox1->Clear();
		maskedTextBox2->Clear();
		comboBox1->Text = "";
		dataGridView2->Rows->Clear();
		dataGridView3->Rows->Clear();
		dataGridView1->Rows->Clear();
		for (int i = 0; i < checkedListBox1->Items->Count; i++) {
			checkedListBox1->SetItemChecked(i, false);
		}
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
	private: System::Void dataGridView2_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		try
		{
			if (e->ColumnIndex == dataGridView2->Columns["deletec"]->Index && e->RowIndex >= 0)
			{
				// Retrieve the index of the row to delete
				int rowIndexToDelete = e->RowIndex;

				// Remove the row from the DataGridView
				dataGridView2->Rows->RemoveAt(rowIndexToDelete);
			}
		}
		catch (...)
		{

		}
	}
	private: System::Void dataGridView3_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		try
		{
			if (e->ColumnIndex == dataGridView3->Columns["Deleteco"]->Index && e->RowIndex >= 0)
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
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to generate the timetable?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
		{
			fstream log;
			log.open("logs/log.txt");
			int k;
			log >> k;
			k++;
			log.close();
			ofstream logg("logs/log.txt");
			logg << k;
			logg.close();
			string newfile = "logs/" + to_string(k) + "teacher.csv";
			string newfile2 = "logs/" + to_string(k) + "building.csv";
			String^ Newfile = msclr::interop::marshal_as<String^>(newfile);
			String^ Newfile2 = msclr::interop::marshal_as<String^>(newfile2);
			String^ originalfile1 = "teacher_file.csv";
			String^ originalfile2 = "building.csv";
			String^ dupli1 = "teachercopy.csv";
			String^ dupli2 = "buidingcopy.csv";
			over(Newfile, originalfile1);
			over(Newfile2, originalfile2);
			over(originalfile1, dupli1);
			over(originalfile2, dupli2);
		}
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void panel3_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
private: System::Void dataGridView3_CellContentClick_1(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	Form::Close();
}
private: System::Void maskedTextBox2_MaskInputRejected(System::Object^ sender, System::Windows::Forms::MaskInputRejectedEventArgs^ e) {
}
};
}
