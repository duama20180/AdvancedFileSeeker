#pragma once
#include "SearchEngine.h"
#include "AboutForm.h"
#include "HelpForm.h"
namespace AdvancedFileSeeker {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    private:
        String^ selectedFile; // Зберігання вибраного файлу
        String^ searchMode;   // Режим пошуку
        String^ regexSearchType; // Тип пошуку регулярним виразом

    private: System::Windows::Forms::StatusStrip^ statusStrip1;
    private: System::Windows::Forms::ToolStripStatusLabel^ statusLabel; // Статус програми
    private: System::Windows::Forms::ToolStripStatusLabel^ pathLabel;   // Вибраний шлях
    private: System::Windows::Forms::ToolStripStatusLabel^ foundFilesLabel; // Кількість знайдених файлів
    private: System::Windows::Forms::ToolStripProgressBar^ statusProgressBar; // Прогрес у StatusStrip

    public:
        MainForm(void)
        {
            InitializeComponent();
            listView->View = View::Details;
            listView->HeaderStyle = ColumnHeaderStyle::None;
            listView->Columns->Add(L"Ім'я файлу", 200);
            listView->Columns->Add(L"Шлях до файлу", 420);
            listView->Columns->Add(L"Розмір", 80);

            searchMode = L"Рег. вирази";
            regexSearchType = L"У назві файлу";

            System::Diagnostics::Debug::WriteLine("MainForm initialized");
            treeView->AfterSelect += gcnew TreeViewEventHandler(this, &MainForm::treeView_AfterSelect);

            tsChoseFile->Click += gcnew EventHandler(this, &MainForm::tsChoseFile_Click);
            tsChoseFolder->Click += gcnew EventHandler(this, &MainForm::tsChoseFolder_Click);
            tsExitFromPath->Click += gcnew EventHandler(this, &MainForm::tsExitFromPath_Click);
            tsSearch->Click += gcnew EventHandler(this, &MainForm::tsSearch_Click);
            tsCancel->Click += gcnew EventHandler(this, &MainForm::tsCancel_Click);
            tsHelp->Click += gcnew EventHandler(this, &MainForm::tsHelp_Click);
            tsExitProgram->Click += gcnew EventHandler(this, &MainForm::tsExitProgram_Click);

            tsMiOpenFile->Click += gcnew EventHandler(this, &MainForm::tsChoseFile_Click);
            tsMiOpenFolder->Click += gcnew EventHandler(this, &MainForm::tsChoseFolder_Click);
            tsMiExit->Click += gcnew EventHandler(this, &MainForm::tsExitProgram_Click);
            tsMiSearch->Click += gcnew EventHandler(this, &MainForm::tsSearch_Click);
            tsMiStopSearch->Click += gcnew EventHandler(this, &MainForm::tsCancel_Click);
            tsMiSetSearch->Click += gcnew EventHandler(this, &MainForm::tsMiSetSearch_Click);

            array<ToolStripMenuItem^>^ searchModes = gcnew array<ToolStripMenuItem^>{
                gcnew ToolStripMenuItem(L"Рег. вирази"),
                gcnew ToolStripMenuItem(L"Ім'я файлу"),
                gcnew ToolStripMenuItem(L"За вмістом"),
                gcnew ToolStripMenuItem(L"За метаданими")
            };

            array<ToolStripMenuItem^>^ regexOptions = gcnew array<ToolStripMenuItem^>{
                gcnew ToolStripMenuItem(L"У назві файлу"),
                gcnew ToolStripMenuItem(L"У вмісті файлу"),
                gcnew ToolStripMenuItem(L"У метаданих (розширення)"),
                gcnew ToolStripMenuItem(L"У метаданих (розмір)"),
                gcnew ToolStripMenuItem(L"У метаданих (дата)")
            };

            for each(ToolStripMenuItem ^ item in searchModes) {
                item->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
                item->Click += gcnew EventHandler(this, &MainForm::tsDropDownSetSearchMode_Click);
                if (item->Text == L"Рег. вирази") {
                    item->DropDownItems->AddRange(regexOptions);
                }
            }

            for each(ToolStripMenuItem ^ regexItem in regexOptions) {
                regexItem->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
                regexItem->Click += gcnew EventHandler(this, &MainForm::tsDropDownSetSearchRegexType_Click);
            }

            tsdDSetSearch->DropDownItems->AddRange(searchModes);

            statusLabel->Text = L"Готово";
            pathLabel->Text = L"Вибраний шлях: (не вибрано)";
            foundFilesLabel->Text = L"Знайдених файлів: 0";
            foundFilesLabel->Visible = false;
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::TreeView^ treeView;
    private: System::Windows::Forms::ListView^ listView;
    private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
    private: System::Windows::Forms::MenuStrip^ mainStrip;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiFileOpen;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiProcess;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiInfo;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiHelp;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiAbout;
    private: System::Windows::Forms::ToolStrip^ toolStrip;
    private: System::Windows::Forms::ToolStripButton^ tsChoseFile;
    private: System::Windows::Forms::ToolStripButton^ tsChoseFolder;
    private: System::Windows::Forms::ToolStripButton^ tsExitFromPath;
    private: System::Windows::Forms::ToolStripButton^ tsSearch;
    private: System::Windows::Forms::ToolStripDropDownButton^ tsdDSetSearch;
    private: System::Windows::Forms::ToolStripButton^ tsCancel;
    private: System::Windows::Forms::ToolStripButton^ tsExitProgram;
    private: System::Windows::Forms::ToolStripButton^ tsHelp;
    private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
    private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator2;
    private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator3;
    private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator4;
    private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator5;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiOpenFile;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiOpenFolder;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiExit;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiSearch;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiStopSearch;
    private: System::Windows::Forms::ToolStripMenuItem^ tsMiSetSearch;
    private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator6;
    private: System::Windows::Forms::TextBox^ tsSearchTB;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
               this->mainStrip = (gcnew System::Windows::Forms::MenuStrip());
               this->tsMiFileOpen = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tsMiOpenFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tsMiOpenFolder = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
               this->tsMiExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tsMiProcess = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tsMiSearch = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tsMiStopSearch = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tsMiSetSearch = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tsMiInfo = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tsMiHelp = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->tsMiAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->treeView = (gcnew System::Windows::Forms::TreeView());
               this->listView = (gcnew System::Windows::Forms::ListView());
               this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
               this->toolStrip = (gcnew System::Windows::Forms::ToolStrip());
               this->tsChoseFile = (gcnew System::Windows::Forms::ToolStripButton());
               this->tsChoseFolder = (gcnew System::Windows::Forms::ToolStripButton());
               this->tsExitFromPath = (gcnew System::Windows::Forms::ToolStripButton());
               this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
               this->tsSearch = (gcnew System::Windows::Forms::ToolStripButton());
               this->tsdDSetSearch = (gcnew System::Windows::Forms::ToolStripDropDownButton());
               this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
               this->tsCancel = (gcnew System::Windows::Forms::ToolStripButton());
               this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
               this->tsHelp = (gcnew System::Windows::Forms::ToolStripButton());
               this->tsExitProgram = (gcnew System::Windows::Forms::ToolStripButton());
               this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
               this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
               this->tsSearchTB = (gcnew System::Windows::Forms::TextBox());
               this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
               this->statusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
               this->pathLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
               this->foundFilesLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
               this->statusProgressBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
               this->mainStrip->SuspendLayout();
               this->toolStrip->SuspendLayout();
               this->statusStrip1->SuspendLayout();
               this->SuspendLayout();
               // 
               // mainStrip
               // 
               this->mainStrip->ImageScalingSize = System::Drawing::Size(20, 20);
               this->mainStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                   this->tsMiFileOpen, this->tsMiProcess,
                       this->tsMiInfo
               });
               this->mainStrip->Location = System::Drawing::Point(0, 0);
               this->mainStrip->Name = L"mainStrip";
               this->mainStrip->Size = System::Drawing::Size(1145, 28);
               this->mainStrip->TabIndex = 0;
               // 
               // tsMiFileOpen
               // 
               this->tsMiFileOpen->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                   this->tsMiOpenFile,
                       this->tsMiOpenFolder, this->toolStripSeparator6, this->tsMiExit
               });
               this->tsMiFileOpen->Name = L"tsMiFileOpen";
               this->tsMiFileOpen->Size = System::Drawing::Size(59, 24);
               this->tsMiFileOpen->Text = L"Файл";
               // 
               // tsMiOpenFile
               // 
               this->tsMiOpenFile->Name = L"tsMiOpenFile";
               this->tsMiOpenFile->Size = System::Drawing::Size(197, 26);
               this->tsMiOpenFile->Text = L"Відкрити файл";
               // 
               // tsMiOpenFolder
               // 
               this->tsMiOpenFolder->Name = L"tsMiOpenFolder";
               this->tsMiOpenFolder->Size = System::Drawing::Size(197, 26);
               this->tsMiOpenFolder->Text = L"Відкрити папку";
               // 
               // toolStripSeparator6
               // 
               this->toolStripSeparator6->Name = L"toolStripSeparator6";
               this->toolStripSeparator6->Size = System::Drawing::Size(194, 6);
               // 
               // tsMiExit
               // 
               this->tsMiExit->Name = L"tsMiExit";
               this->tsMiExit->Size = System::Drawing::Size(197, 26);
               this->tsMiExit->Text = L"Вийти";
               // 
               // tsMiProcess
               // 
               this->tsMiProcess->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                   this->tsMiSearch,
                       this->tsMiStopSearch, this->tsMiSetSearch
               });
               this->tsMiProcess->Name = L"tsMiProcess";
               this->tsMiProcess->Size = System::Drawing::Size(76, 24);
               this->tsMiProcess->Text = L"Процес";
               // 
               // tsMiSearch
               // 
               this->tsMiSearch->Name = L"tsMiSearch";
               this->tsMiSearch->Size = System::Drawing::Size(249, 26);
               this->tsMiSearch->Text = L"Пошук";
               // 
               // tsMiStopSearch
               // 
               this->tsMiStopSearch->Name = L"tsMiStopSearch";
               this->tsMiStopSearch->Size = System::Drawing::Size(249, 26);
               this->tsMiStopSearch->Text = L"Зупинити пошук";
               // 
               // tsMiSetSearch
               // 
               this->tsMiSetSearch->Name = L"tsMiSetSearch";
               this->tsMiSetSearch->Size = System::Drawing::Size(249, 26);
               this->tsMiSetSearch->Text = L"Налаштування пошуку";
               // 
               // tsMiInfo
               // 
               this->tsMiInfo->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->tsMiHelp, this->tsMiAbout });
               this->tsMiInfo->Name = L"tsMiInfo";
               this->tsMiInfo->Size = System::Drawing::Size(55, 24);
               this->tsMiInfo->Text = L"Інфо";
               // 
               // tsMiHelp
               // 
               this->tsMiHelp->Name = L"tsMiHelp";
               this->tsMiHelp->Size = System::Drawing::Size(193, 26);
               this->tsMiHelp->Text = L"Довідка";
               this->tsMiHelp->Click += gcnew System::EventHandler(this, &MainForm::newHelpToolStripMenuItem_Click);
               // 
               // tsMiAbout
               // 
               this->tsMiAbout->Name = L"tsMiAbout";
               this->tsMiAbout->Size = System::Drawing::Size(193, 26);
               this->tsMiAbout->Text = L"Про програму";
               this->tsMiAbout->Click += gcnew System::EventHandler(this, &MainForm::newAboutToolStripMenuItem_Click);
               // 
               // treeView
               // 
               this->treeView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                   | System::Windows::Forms::AnchorStyles::Left));
               this->treeView->Location = System::Drawing::Point(0, 111);
               this->treeView->Name = L"treeView";
               this->treeView->Size = System::Drawing::Size(323, 523);
               this->treeView->TabIndex = 1;
               this->treeView->BeforeExpand += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &MainForm::treeView_BeforeExpand);
               // 
               // listView
               // 
               this->listView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                   | System::Windows::Forms::AnchorStyles::Left)
                   | System::Windows::Forms::AnchorStyles::Right));
               this->listView->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(204)));
               this->listView->HideSelection = false;
               this->listView->Location = System::Drawing::Point(327, 111);
               this->listView->Name = L"listView";
               this->listView->Size = System::Drawing::Size(818, 523);
               this->listView->TabIndex = 4;
               this->listView->UseCompatibleStateImageBehavior = false;
               // 
               // backgroundWorker1
               // 
               this->backgroundWorker1->WorkerReportsProgress = true;
               this->backgroundWorker1->WorkerSupportsCancellation = true;
               this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker1_DoWork);
               this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MainForm::backgroundWorker1_ProgressChanged);
               this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainForm::backgroundWorker1_RunWorkerCompleted);
               // 
               // toolStrip
               // 
               this->toolStrip->CanOverflow = false;
               this->toolStrip->Dock = System::Windows::Forms::DockStyle::None;
               this->toolStrip->ImageScalingSize = System::Drawing::Size(36, 36);
               this->toolStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
                   this->tsChoseFile, this->tsChoseFolder,
                       this->tsExitFromPath, this->toolStripSeparator1, this->tsSearch, this->tsdDSetSearch, this->toolStripSeparator2, this->tsCancel,
                       this->toolStripSeparator3, this->tsHelp, this->tsExitProgram
               });
               this->toolStrip->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
               this->toolStrip->Location = System::Drawing::Point(0, 28);
               this->toolStrip->Name = L"toolStrip";
               this->toolStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
               this->toolStrip->Size = System::Drawing::Size(361, 43);
               this->toolStrip->TabIndex = 7;
               this->toolStrip->Text = L"toolStrip1";
               // 
               // tsChoseFile
               // 
               this->tsChoseFile->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
               this->tsChoseFile->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsChoseFile.Image")));
               this->tsChoseFile->ImageTransparentColor = System::Drawing::Color::Magenta;
               this->tsChoseFile->Name = L"tsChoseFile";
               this->tsChoseFile->Size = System::Drawing::Size(40, 40);
               this->tsChoseFile->ToolTipText = L"Вибрати файл";
               // 
               // tsChoseFolder
               // 
               this->tsChoseFolder->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
               this->tsChoseFolder->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsChoseFolder.Image")));
               this->tsChoseFolder->ImageTransparentColor = System::Drawing::Color::Magenta;
               this->tsChoseFolder->Name = L"tsChoseFolder";
               this->tsChoseFolder->Size = System::Drawing::Size(40, 40);
               this->tsChoseFolder->ToolTipText = L"Вибрати папку";
               // 
               // tsExitFromPath
               // 
               this->tsExitFromPath->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
               this->tsExitFromPath->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsExitFromPath.Image")));
               this->tsExitFromPath->ImageTransparentColor = System::Drawing::Color::Magenta;
               this->tsExitFromPath->Name = L"tsExitFromPath";
               this->tsExitFromPath->Size = System::Drawing::Size(40, 40);
               this->tsExitFromPath->ToolTipText = L"Вийти з шляху";
               // 
               // toolStripSeparator1
               // 
               this->toolStripSeparator1->Name = L"toolStripSeparator1";
               this->toolStripSeparator1->Size = System::Drawing::Size(6, 43);
               // 
               // tsSearch
               // 
               this->tsSearch->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
               this->tsSearch->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsSearch.Image")));
               this->tsSearch->ImageTransparentColor = System::Drawing::Color::Magenta;
               this->tsSearch->Name = L"tsSearch";
               this->tsSearch->Size = System::Drawing::Size(40, 40);
               this->tsSearch->ToolTipText = L"Пошук";
               // 
               // tsdDSetSearch
               // 
               this->tsdDSetSearch->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
               this->tsdDSetSearch->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsdDSetSearch.Image")));
               this->tsdDSetSearch->ImageTransparentColor = System::Drawing::Color::Magenta;
               this->tsdDSetSearch->Name = L"tsdDSetSearch";
               this->tsdDSetSearch->Size = System::Drawing::Size(50, 40);
               this->tsdDSetSearch->ToolTipText = L"Налаштування пошуку";
               // 
               // toolStripSeparator2
               // 
               this->toolStripSeparator2->Name = L"toolStripSeparator2";
               this->toolStripSeparator2->Size = System::Drawing::Size(6, 43);
               // 
               // tsCancel
               // 
               this->tsCancel->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
               this->tsCancel->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsCancel.Image")));
               this->tsCancel->ImageTransparentColor = System::Drawing::Color::Magenta;
               this->tsCancel->Name = L"tsCancel";
               this->tsCancel->Size = System::Drawing::Size(40, 40);
               this->tsCancel->ToolTipText = L"Скасувати";
               // 
               // toolStripSeparator3
               // 
               this->toolStripSeparator3->Name = L"toolStripSeparator3";
               this->toolStripSeparator3->Size = System::Drawing::Size(6, 43);
               // 
               // tsHelp
               // 
               this->tsHelp->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
               this->tsHelp->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsHelp.Image")));
               this->tsHelp->ImageTransparentColor = System::Drawing::Color::Magenta;
               this->tsHelp->Name = L"tsHelp";
               this->tsHelp->Size = System::Drawing::Size(40, 40);
               this->tsHelp->ToolTipText = L"Довідка";
               // 
               // tsExitProgram
               // 
               this->tsExitProgram->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
               this->tsExitProgram->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsExitProgram.Image")));
               this->tsExitProgram->ImageTransparentColor = System::Drawing::Color::Magenta;
               this->tsExitProgram->Name = L"tsExitProgram";
               this->tsExitProgram->Size = System::Drawing::Size(40, 40);
               this->tsExitProgram->ToolTipText = L"Вихід із програми";
               // 
               // toolStripSeparator4
               // 
               this->toolStripSeparator4->Name = L"toolStripSeparator4";
               this->toolStripSeparator4->Size = System::Drawing::Size(6, 6);
               // 
               // toolStripSeparator5
               // 
               this->toolStripSeparator5->Name = L"toolStripSeparator5";
               this->toolStripSeparator5->Size = System::Drawing::Size(6, 6);
               // 
               // tsSearchTB
               // 
               this->tsSearchTB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->tsSearchTB->Location = System::Drawing::Point(12, 81);
               this->tsSearchTB->Name = L"tsSearchTB";
               this->tsSearchTB->Size = System::Drawing::Size(309, 24);
               this->tsSearchTB->TabIndex = 11;
               // 
               // statusStrip1
               // 
               this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
               this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                   this->statusLabel, this->pathLabel,
                       this->foundFilesLabel, this->statusProgressBar
               });
               this->statusStrip1->Location = System::Drawing::Point(0, 637);
               this->statusStrip1->Name = L"statusStrip1";
               this->statusStrip1->Size = System::Drawing::Size(1145, 26);
               this->statusStrip1->TabIndex = 12;
               this->statusStrip1->Text = L"statusStrip1";
               // 
               // statusLabel
               // 
               this->statusLabel->Name = L"statusLabel";
               this->statusLabel->Size = System::Drawing::Size(57, 20);
               this->statusLabel->Text = L"Готово";
               // 
               // pathLabel
               // 
               this->pathLabel->Name = L"pathLabel";
               this->pathLabel->Size = System::Drawing::Size(218, 20);
               this->pathLabel->Text = L"Вибраний шлях: (не вибрано)";
               // 
               // foundFilesLabel
               // 
               this->foundFilesLabel->Name = L"foundFilesLabel";
               this->foundFilesLabel->Size = System::Drawing::Size(150, 20);
               this->foundFilesLabel->Text = L"Знайдених файлів: 0";
               // 
               // statusProgressBar
               // 
               this->statusProgressBar->Name = L"statusProgressBar";
               this->statusProgressBar->Size = System::Drawing::Size(200, 18);
               // 
               // MainForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(1145, 663);
               this->Controls->Add(this->tsSearchTB);
               this->Controls->Add(this->toolStrip);
               this->Controls->Add(this->listView);
               this->Controls->Add(this->treeView);
               this->Controls->Add(this->statusStrip1);
               this->Controls->Add(this->mainStrip);
               this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
               this->MainMenuStrip = this->mainStrip;
               this->MinimumSize = System::Drawing::Size(400, 400);
               this->Name = L"MainForm";
               this->Text = L"Advanced File Seeker";
               this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
               this->mainStrip->ResumeLayout(false);
               this->mainStrip->PerformLayout();
               this->toolStrip->ResumeLayout(false);
               this->toolStrip->PerformLayout();
               this->statusStrip1->ResumeLayout(false);
               this->statusStrip1->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

    private: System::Void treeView_BeforeExpand(System::Object^ sender, System::Windows::Forms::TreeViewCancelEventArgs^ e) {
        TreeNode^ node = e->Node;
        node->Nodes->Clear();
        try {
            array<String^>^ dirs = Directory::GetDirectories(node->FullPath);
            for each(String ^ dir in dirs) {
                TreeNode^ subNode = gcnew TreeNode(Path::GetFileName(dir));
                subNode->Tag = dir;
                subNode->Nodes->Add("dummy");
                node->Nodes->Add(subNode);
            }
        }
        catch (Exception^ ex) {
            e->Cancel = true;
        }
    }

    private: System::Void treeView_AfterSelect(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e) {
        String^ selectedPath = (e->Node->Tag != nullptr) ? safe_cast<String^>(e->Node->Tag) : e->Node->FullPath;
        pathLabel->Text = L"Вибраний шлях: " + selectedPath;
    }

    private: System::Void tsSearch_Click(System::Object^ sender, System::EventArgs^ e) {
        if (backgroundWorker1->IsBusy) {
            System::Diagnostics::Debug::WriteLine("BackgroundWorker is busy, cannot start new search.");
            return;
        }

        System::Diagnostics::Debug::WriteLine("Starting new search...");

        listView->Items->Clear();
        listView->HeaderStyle = ColumnHeaderStyle::None;
        foundFilesLabel->Text = L"Знайдених файлів: 0";
        foundFilesLabel->Visible = false;
        statusLabel->Text = L"Пошук...";

        System::Diagnostics::Debug::WriteLine("Setting tsCancel->Enabled to true");
        tsCancel->Enabled = true;
        this->Refresh();

        String^ searchText = tsSearchTB->Text;

        if (String::IsNullOrEmpty(searchText)) {
            MessageBox::Show(L"Введіть критерій пошуку!", L"Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            statusProgressBar->Value = 0;
            tsCancel->Enabled = false;
            statusLabel->Text = L"Помилка: критерій пошуку не введено";
            System::Diagnostics::Debug::WriteLine("Search cancelled due to empty search text.");
            return;
        }

        statusProgressBar->Minimum = 0;
        statusProgressBar->Maximum = 100;
        statusProgressBar->Value = 10;

        String^ directory = nullptr;
        if (selectedFile != nullptr) {
            directory = selectedFile;
        }
        else if (treeView->SelectedNode != nullptr && treeView->SelectedNode->Tag != nullptr) {
            directory = safe_cast<String^>(treeView->SelectedNode->Tag);
        }
        else {
            directory = "C:\\";
        }

        array<Object^>^ parameters = gcnew array<Object^>{ directory, searchText, searchMode, regexSearchType };
        backgroundWorker1->RunWorkerAsync(parameters);

        for (int i = 10; i <= 30 && backgroundWorker1->IsBusy; i += 5) {
            statusProgressBar->Value = i;
            System::Threading::Thread::Sleep(100);
        }
    }

    private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
        array<Object^>^ parameters = safe_cast<array<Object^>^>(e->Argument);
        String^ directory = safe_cast<String^>(parameters[0]);
        String^ searchText = safe_cast<String^>(parameters[1]);
        String^ searchMode = safe_cast<String^>(parameters[2]);
        String^ regexSearchType = parameters->Length > 3 ? safe_cast<String^>(parameters[3]) : nullptr;

        OnProgressEvent^ progressDelegate = gcnew OnProgressEvent(this, &MainForm::ReportProgress);
        array<String^>^ files;

        try {
            if (File::Exists(directory)) {
                files = gcnew array<String^>{ directory };
            }
            else if (searchMode == L"Ім'я файлу") {
                files = SearchEngine::SearchByName(directory, "*" + searchText + "*", progressDelegate, backgroundWorker1);
            }
            else if (searchMode == L"За вмістом") {
                files = SearchEngine::SearchByContent(directory, searchText, progressDelegate, backgroundWorker1);
            }
            else if (searchMode == L"Рег. вирази") {
                if (regexSearchType == L"У назві файлу") {
                    files = SearchEngine::SearchByRegex(directory, searchText, "name", progressDelegate, backgroundWorker1);
                }
                else if (regexSearchType == L"У вмісті файлу") {
                    files = SearchEngine::SearchByRegex(directory, searchText, "content", progressDelegate, backgroundWorker1);
                }
                else if (regexSearchType == L"У метаданих (розширення)") {
                    files = SearchEngine::SearchByRegex(directory, searchText, "extension", progressDelegate, backgroundWorker1);
                }
                else if (regexSearchType == L"У метаданих (розмір)") {
                    files = SearchEngine::SearchByRegex(directory, searchText, "size", progressDelegate, backgroundWorker1);
                }
                else if (regexSearchType == L"У метаданих (дата)") {
                    files = SearchEngine::SearchByRegex(directory, searchText, "date", progressDelegate, backgroundWorker1);
                }
                else {
                    files = gcnew array<String^>(0);
                }
            }
            else if (searchMode == L"За метаданими") {
                files = SearchEngine::SearchByMetadata(directory, searchText, L"extension", progressDelegate, backgroundWorker1);
            }
            else {
                e->Result = nullptr;
                return;
            }
            e->Result = files;
        }
        catch (Exception^ ex) {
            e->Result = nullptr;
        }
    }

    private: void ReportProgress(int progress) {
        if (progress > 30) {
            backgroundWorker1->ReportProgress(progress);
        }
    }

    private: System::Void backgroundWorker1_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e) {
        if (e->ProgressPercentage > 0 && e->ProgressPercentage <= statusProgressBar->Maximum) {
            statusProgressBar->Value = e->ProgressPercentage;
        }
    }

    private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
        statusProgressBar->Value = 97;
        System::Threading::Thread::Sleep(300);
        statusProgressBar->Value = 100;

        System::Diagnostics::Debug::WriteLine("Search completed.");
        tsCancel->Enabled = false;

        if (e->Cancelled) {
            array<String^>^ files = safe_cast<array<String^>^>(e->Result);
            if (files != nullptr) {
                for each(String ^ file in files) {
                    ListViewItem^ item = SearchEngine::CreateListViewItemForFile(file);
                    listView->Items->Add(item);
                }
                foundFilesLabel->Text = L"Знайдених файлів: " + files->Length.ToString();
                foundFilesLabel->Visible = true;
                if (files->Length > 0) {
                    listView->HeaderStyle = ColumnHeaderStyle::Clickable;
                }
                statusLabel->Text = L"Пошук зупинено";
                System::Diagnostics::Debug::WriteLine("Search was cancelled. Found " + files->Length + " files before cancellation.");
            }
            else {
                foundFilesLabel->Text = L"Знайдених файлів: 0";
                foundFilesLabel->Visible = true;
                listView->HeaderStyle = ColumnHeaderStyle::None;
                statusLabel->Text = L"Пошук зупинено";
                System::Diagnostics::Debug::WriteLine("Search was cancelled with no results.");
            }
        }
        else if (e->Error != nullptr) {
            MessageBox::Show(L"Помилка під час пошуку: " + e->Error->Message, L"Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            foundFilesLabel->Text = L"Знайдених файлів: 0";
            foundFilesLabel->Visible = true;
            listView->HeaderStyle = ColumnHeaderStyle::None;
            statusLabel->Text = L"Помилка";
            System::Diagnostics::Debug::WriteLine("Search failed with error: " + e->Error->Message);
        }
        else if (e->Result != nullptr) {
            array<String^>^ files = safe_cast<array<String^>^>(e->Result);
            for each(String ^ file in files) {
                ListViewItem^ item = SearchEngine::CreateListViewItemForFile(file);
                listView->Items->Add(item);
            }
            foundFilesLabel->Text = L"Знайдених файлів: " + files->Length.ToString();
            foundFilesLabel->Visible = true;
            if (files->Length > 0) {
                listView->HeaderStyle = ColumnHeaderStyle::Clickable;
            }
            statusLabel->Text = L"Пошук завершено";
            System::Diagnostics::Debug::WriteLine("Search completed successfully. Found " + files->Length + " files.");
        }
        else {
            foundFilesLabel->Text = L"Знайдених файлів: 0";
            foundFilesLabel->Visible = true;
            listView->HeaderStyle = ColumnHeaderStyle::None;
            statusLabel->Text = L"Пошук завершено";
            System::Diagnostics::Debug::WriteLine("Search completed with no results.");
        }

        statusProgressBar->Value = 0;
    }

    private: void InitializeTreeView() {
        for each(DriveInfo ^ drive in DriveInfo::GetDrives()) {
            try {
                TreeNode^ node = gcnew TreeNode(drive->Name);
                node->Tag = drive->Name;
                node->Nodes->Add("dummy");
                treeView->Nodes->Add(node);
                System::Diagnostics::Debug::WriteLine("Added drive: " + drive->Name);
            }
            catch (Exception^ ex) {
                System::Diagnostics::Debug::WriteLine("Drive init error: " + ex->Message);
            }
        }
    }

    private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
        InitializeTreeView();
    }

    private: System::Void newHelpToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
        HelpForm^ helpForm = gcnew HelpForm();
        helpForm->StartPosition = FormStartPosition::CenterParent;
        helpForm->ShowDialog();
    }

    private: System::Void newAboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
        AboutForm^ aboutForm = gcnew AboutForm();
        aboutForm->StartPosition = FormStartPosition::CenterParent;
        aboutForm->ShowDialog();
    }

    private: System::Void tsChoseFile_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::OpenFileDialog^ ofd = gcnew System::Windows::Forms::OpenFileDialog();
        ofd->Title = L"Вибрати файл для пошуку";
        ofd->Filter = L"Усі файли (*.*)|*.*";
        if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            selectedFile = ofd->FileName;
            pathLabel->Text = L"Вибраний файл: " + selectedFile;
            treeView->SelectedNode = nullptr;
        }
    }

    private: System::Void tsChoseFolder_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::FolderBrowserDialog^ fbd = gcnew System::Windows::Forms::FolderBrowserDialog();
        fbd->Description = L"Вибрати папку для пошуку";
        if (fbd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            String^ selectedFolder = fbd->SelectedPath;
            TreeNode^ node = gcnew TreeNode(Path::GetFileName(selectedFolder));
            node->Tag = selectedFolder;
            node->Nodes->Add("dummy");
            treeView->Nodes->Clear();
            treeView->Nodes->Add(node);
            treeView->SelectedNode = node;
            selectedFile = nullptr;
            pathLabel->Text = L"Вибраний шлях: " + selectedFolder;
        }
    }

    private: System::Void tsExitFromPath_Click(System::Object^ sender, System::EventArgs^ e) {
        selectedFile = nullptr;
        treeView->Nodes->Clear();
        InitializeTreeView();
        pathLabel->Text = L"Вибраний шлях: (не вибрано)";
    }

    private: System::Void tsDropDownSetSearchMode_Click(System::Object^ sender, System::EventArgs^ e) {
        ToolStripMenuItem^ selectedItem = safe_cast<ToolStripMenuItem^>(sender);
        searchMode = selectedItem->Text;
    }

    private: System::Void tsDropDownSetSearchRegexType_Click(System::Object^ sender, System::EventArgs^ e) {
        ToolStripMenuItem^ selectedItem = safe_cast<ToolStripMenuItem^>(sender);
        regexSearchType = selectedItem->Text;
        searchMode = L"Рег. вирази";
    }

    private: System::Void tsCancel_Click(System::Object^ sender, System::EventArgs^ e) {
        if (backgroundWorker1->IsBusy) {
            backgroundWorker1->CancelAsync();
            MessageBox::Show(L"Пошук зупинено", L"Сповіщення", MessageBoxButtons::OK, MessageBoxIcon::Information);
            tsCancel->Enabled = false;
            statusLabel->Text = L"Пошук зупинено";
            System::Diagnostics::Debug::WriteLine("Search stopped by user.");
        }
    }

    private: System::Void tsHelp_Click(System::Object^ sender, System::EventArgs^ e) {
        HelpForm^ helpForm = gcnew HelpForm();
        helpForm->StartPosition = FormStartPosition::CenterParent;
        helpForm->ShowDialog();
    }

    private: System::Void tsExitProgram_Click(System::Object^ sender, System::EventArgs^ e) {
        Application::Exit();
    }

    private: System::Void tsMiSetSearch_Click(System::Object^ sender, System::EventArgs^ e) {
        Form^ settingsForm = gcnew Form();
        settingsForm->Text = L"Налаштування пошуку";
        settingsForm->Size = System::Drawing::Size(300, 250);
        settingsForm->StartPosition = FormStartPosition::CenterParent;
        settingsForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        settingsForm->MaximizeBox = false;
        settingsForm->MinimizeBox = false;

        Label^ modeLabel = gcnew Label();
        modeLabel->Text = L"Виберіть режим пошуку:";
        modeLabel->Location = System::Drawing::Point(20, 20);
        modeLabel->AutoSize = true;
        settingsForm->Controls->Add(modeLabel);

        ComboBox^ searchModeComboBox = gcnew ComboBox();
        searchModeComboBox->DropDownStyle = ComboBoxStyle::DropDownList;
        searchModeComboBox->Items->AddRange(gcnew array<String^> {
            L"Рег. вирази",
                L"Ім'я файлу",
                L"За вмістом",
                L"За метаданими"
        });
        searchModeComboBox->SelectedItem = searchMode;
        searchModeComboBox->Location = System::Drawing::Point(20, 50);
        searchModeComboBox->Size = System::Drawing::Size(200, 30);
        settingsForm->Controls->Add(searchModeComboBox);

        Label^ regexLabel = gcnew Label();
        regexLabel->Text = L"Тип пошуку для рег. виразу:";
        regexLabel->Location = System::Drawing::Point(20, 90);
        regexLabel->AutoSize = true;
        settingsForm->Controls->Add(regexLabel);

        ComboBox^ regexTypeComboBox = gcnew ComboBox();
        regexTypeComboBox->DropDownStyle = ComboBoxStyle::DropDownList;
        regexTypeComboBox->Items->AddRange(gcnew array<String^> {
            L"У назві файлу",
                L"У вмісті файлу",
                L"У метаданих (розширення)",
                L"У метаданих (розмір)",
                L"У метаданих (дата)"
        });
        regexTypeComboBox->SelectedItem = regexSearchType;
        regexTypeComboBox->Location = System::Drawing::Point(20, 120);
        regexTypeComboBox->Size = System::Drawing::Size(200, 30);
        settingsForm->Controls->Add(regexTypeComboBox);

        Button^ okButton = gcnew Button();
        okButton->Text = L"OK";
        okButton->Location = System::Drawing::Point(20, 160);
        okButton->Click += gcnew EventHandler(this, &MainForm::SearchSettingsOk_Click);
        settingsForm->Controls->Add(okButton);

        Button^ cancelButton = gcnew Button();
        cancelButton->Text = L"Скасувати";
        cancelButton->Location = System::Drawing::Point(100, 160);
        cancelButton->Click += gcnew EventHandler(this, &MainForm::SearchSettingsCancel_Click);
        settingsForm->Controls->Add(cancelButton);

        settingsForm->Tag = gcnew array<ComboBox^>{ searchModeComboBox, regexTypeComboBox };

        settingsForm->ShowDialog();
    }

    private: System::Void SearchSettingsOk_Click(System::Object^ sender, System::EventArgs^ e) {
        Button^ button = safe_cast<Button^>(sender);
        Form^ form = safe_cast<Form^>(button->Parent);
        array<ComboBox^>^ comboBoxes = safe_cast<array<ComboBox^>^>(form->Tag);
        ComboBox^ searchModeComboBox = comboBoxes[0];
        ComboBox^ regexTypeComboBox = comboBoxes[1];
        searchMode = safe_cast<String^>(searchModeComboBox->SelectedItem);
        regexSearchType = safe_cast<String^>(regexTypeComboBox->SelectedItem);
        form->Close();
    }

    private: System::Void SearchSettingsCancel_Click(System::Object^ sender, System::EventArgs^ e) {
        Button^ button = safe_cast<Button^>(sender);
        Form^ form = safe_cast<Form^>(button->Parent);
        form->Close();
    }
    };
}