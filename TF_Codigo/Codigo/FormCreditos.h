#pragma once
#include "Biblioteca.h"

namespace Codigo {

	public ref class FormCreditos : public Form
	{
	public:
		FormCreditos(void)
		{
			InitializeComponent();
		}

	protected:
		~FormCreditos()
		{
			delete Salir;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Salir;
	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(FormCreditos::typeid));
			this->Salir = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Salir
			// 
			this->Salir->BackColor = System::Drawing::Color::Transparent;
			this->Salir->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Salir.BackgroundImage")));
			this->Salir->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Salir->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->Salir->Location = System::Drawing::Point(493, 327);
			this->Salir->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Salir->Name = L"Salir";
			this->Salir->Size = System::Drawing::Size(35, 32);
			this->Salir->TabIndex = 0;
			this->Salir->UseVisualStyleBackColor = false;
			this->Salir->Click += gcnew System::EventHandler(this, &FormCreditos::Salir_Click);
			// 
			// FormCreditos
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(533, 369);
			this->Controls->Add(this->Salir);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"FormCreditos";
			this->Text = L"Creditos";
			this->Load += gcnew System::EventHandler(this, &FormCreditos::FormCreditos_Load);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Icon = gcnew System::Drawing::Icon("..\\SpriteFinalizados\\logo.ico");
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Salir_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void FormCreditos_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
