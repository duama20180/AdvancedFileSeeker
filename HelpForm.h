#pragma once

namespace AdvancedFileSeeker {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class HelpForm : public System::Windows::Forms::Form
    {
    public:
        HelpForm(void)
        {
            InitializeComponent();
            InitializeHelpContent();
        }

    protected:
        ~HelpForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::RichTextBox^ richTextBox1;
    protected:

    protected:


    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(HelpForm::typeid));
               this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
               this->SuspendLayout();
               // 
               // richTextBox1
               // 
               this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Consolas", 10));
               this->richTextBox1->Location = System::Drawing::Point(12, 12);
               this->richTextBox1->Name = L"richTextBox1";
               this->richTextBox1->ReadOnly = true;
               this->richTextBox1->Size = System::Drawing::Size(633, 400);
               this->richTextBox1->TabIndex = 0;
               this->richTextBox1->Text = L"";
               // 
               // HelpForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(657, 424);
               this->Controls->Add(this->richTextBox1);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
               this->MaximizeBox = false;
               this->MinimizeBox = false;
               this->Name = L"HelpForm";
               this->Text = L"Довідка";
               this->ResumeLayout(false);

           }
#pragma endregion

    private: void InitializeHelpContent() {
        richTextBox1->Text =
            L"=== Довідка з регулярних виразів ===\n\n"
            L"Регулярні вирази (RegEx) — це шаблони для пошуку та обробки тексту. У цій програмі вони використовуються для пошуку файлів за складними критеріями.\n\n"
            L"--- Основна структура ---\n"
            L"1. Символи:\n"
            L"   - a-z, 0-9 — шукає конкретний символ.\n"
            L"   - . — будь-який символ.\n"
            L"   - \\d — будь-яка цифра (0-9).\n"
            L"   - \\w — будь-який буквено-цифровий символ (a-z, A-Z, 0-9, _).\n"
            L"   - \\s — пробіл або табуляція.\n\n"
            L"2. Квантифікатори:\n"
            L"   - * — 0 або більше повторів.\n"
            L"   - + — 1 або більше повторів.\n"
            L"   - ? — 0 або 1 повтор.\n"
            L"   - {n} — точно n повторів.\n"
            L"   - {n,m} — від n до m повторів.\n\n"
            L"3. Групи та діапазони:\n"
            L"   - [abc] — один із символів a, b, c.\n"
            L"   - [a-z] — будь-яка мала літера.\n"
            L"   - [^abc] — будь-який символ, крім a, b, c.\n"
            L"   - (abc) — групує 'abc' як єдине ціле.\n\n"
            L"4. Спеціальні символи:\n"
            L"   - ^ — початок рядка.\n"
            L"   - $ — кінець рядка.\n"
            L"   - | — або (наприклад, cat|dog).\n"
            L"   - \\ — екранування спеціальних символів (наприклад, \\. для крапки).\n\n"
            L"--- Приклади ---\n"
            L"1. Пошук файлів з розширенням .txt:\n"
            L"   - Шаблон: \\.txt$\n"
            L"   - Пояснення: шукає файли, що закінчуються на '.txt'.\n\n"
            L"2. Файли, що починаються з 'test' і мають цифри:\n"
            L"   - Шаблон: ^test\\d+\n"
            L"   - Пояснення: '^test' — початок із 'test', '\\d+' — одна або більше цифр.\n\n"
            L"3. Файли з будь-яким числом між 'file' і '.doc':\n"
            L"   - Шаблон: file\\d+\\.doc\n"
            L"   - Пояснення: 'file', потім цифри, потім '.doc'.\n\n"
            L"4. Пошук файлів із розширеннями .jpg або .png:\n"
            L"   - Шаблон: \\.(jpg|png)$\n"
            L"   - Пояснення: '\\.' — крапка, '(jpg|png)' — або 'jpg', або 'png', '$' — кінець.\n\n"
            L"--- Поради ---\n"
            L"- Перевіряйте шаблони заздалегідь за допомогою наявної кнопки.\n"
            L"- Уникайте надто загальних шаблонів (наприклад, '.*'), щоб пришвидшити пошук.";
    }
    };
}