#pragma once

namespace AdvancedFileSeeker {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class AboutForm : public System::Windows::Forms::Form
	{
	public:
		AboutForm(void)
		{
			InitializeComponent();
		}

	protected:

		~AboutForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:

		System::Windows::Forms::PictureBox^ pbIcon;
		System::Windows::Forms::Label^ lblName;
		System::Windows::Forms::Label^ lblVersion;
		System::Windows::Forms::Label^ lblAuthor;
		System::Windows::Forms::Label^ lblRights;
		System::Windows::Forms::Label^ lblInfo;
		System::Windows::Forms::Button^ btnClose;
	private: System::Windows::Forms::Label^ labelName;

	private: System::Windows::Forms::PictureBox^ PictureBox;
	private: System::Windows::Forms::Label^ labelVersion;
	private: System::Windows::Forms::Label^ labelAuthor;




	private: System::Windows::Forms::Label^ labelRights;
	private: System::Windows::Forms::Label^ labelInfo;
	private: System::Windows::Forms::Button^ closeButton;




		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(AboutForm::typeid));
			this->labelName = (gcnew System::Windows::Forms::Label());
			this->PictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->labelVersion = (gcnew System::Windows::Forms::Label());
			this->labelAuthor = (gcnew System::Windows::Forms::Label());
			this->labelRights = (gcnew System::Windows::Forms::Label());
			this->labelInfo = (gcnew System::Windows::Forms::Label());
			this->closeButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// labelName
			// 
			this->labelName->AutoSize = true;
			this->labelName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelName->Location = System::Drawing::Point(179, 40);
			this->labelName->Name = L"labelName";
			this->labelName->Size = System::Drawing::Size(191, 20);
			this->labelName->TabIndex = 0;
			this->labelName->Text = L"Advanced File Seeker";
			this->labelName->Click += gcnew System::EventHandler(this, &AboutForm::label1_Click);
			// 
			// PictureBox
			// 
			this->PictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PictureBox.Image")));
			this->PictureBox->Location = System::Drawing::Point(15, 30);
			this->PictureBox->Name = L"PictureBox";
			this->PictureBox->Size = System::Drawing::Size(128, 128);
			this->PictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->PictureBox->TabIndex = 1;
			this->PictureBox->TabStop = false;
			// 
			// labelVersion
			// 
			this->labelVersion->AutoSize = true;
			this->labelVersion->Location = System::Drawing::Point(179, 73);
			this->labelVersion->Name = L"labelVersion";
			this->labelVersion->Size = System::Drawing::Size(103, 16);
			this->labelVersion->TabIndex = 2;
			this->labelVersion->Text = L"Версія 0.1.5.124";
			// 
			// labelAuthor
			// 
			this->labelAuthor->AutoSize = true;
			this->labelAuthor->Location = System::Drawing::Point(179, 107);
			this->labelAuthor->Name = L"labelAuthor";
			this->labelAuthor->Size = System::Drawing::Size(275, 16);
			this->labelAuthor->TabIndex = 3;
			this->labelAuthor->Text = L"Розробник: ст. гр. 2ПІ-22б Середа Дмитро";
			// 
			// labelRights
			// 
			this->labelRights->AutoSize = true;
			this->labelRights->Location = System::Drawing::Point(179, 142);
			this->labelRights->Name = L"labelRights";
			this->labelRights->Size = System::Drawing::Size(130, 16);
			this->labelRights->TabIndex = 4;
			this->labelRights->Text = L"Всі права захищені";
			// 
			// labelInfo
			// 
			this->labelInfo->AutoSize = true;
			this->labelInfo->Location = System::Drawing::Point(12, 183);
			this->labelInfo->Name = L"labelInfo";
			this->labelInfo->Size = System::Drawing::Size(473, 160);
			this->labelInfo->TabIndex = 5;
			this->labelInfo->Text = resources->GetString(L"labelInfo.Text");
			// 
			// closeButton
			// 
			this->closeButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->closeButton->Location = System::Drawing::Point(202, 359);
			this->closeButton->Name = L"closeButton";
			this->closeButton->Size = System::Drawing::Size(80, 32);
			this->closeButton->TabIndex = 6;
			this->closeButton->Text = L"Закрити";
			this->closeButton->UseVisualStyleBackColor = true;
			this->closeButton->Click += gcnew System::EventHandler(this, &AboutForm::button1_Click);
			// 
			// AboutForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(492, 403);
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->labelInfo);
			this->Controls->Add(this->labelRights);
			this->Controls->Add(this->labelAuthor);
			this->Controls->Add(this->labelVersion);
			this->Controls->Add(this->PictureBox);
			this->Controls->Add(this->labelName);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"AboutForm";
			this->Text = L"Про застосунок";
			this->Load += gcnew System::EventHandler(this, &AboutForm::AboutForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AboutForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}
