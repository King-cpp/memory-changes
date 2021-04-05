#pragma once
#include <Windows.h>
#include "utilities.h"

namespace CLRHack {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ AddSun;
	protected:

	private: System::Windows::Forms::CheckBox^ FreezeSun;
	private: System::Windows::Forms::CheckBox^ NoDelay;
	protected:


	private: System::Windows::Forms::TextBox^ EditSun;
	private: System::Windows::Forms::Timer^ Timer_FindGame;
	private: System::Windows::Forms::Label^ Label_GameInfo;
	private: System::Windows::Forms::GroupBox^ GroupAll;



	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->AddSun = (gcnew System::Windows::Forms::Button());
			this->FreezeSun = (gcnew System::Windows::Forms::CheckBox());
			this->NoDelay = (gcnew System::Windows::Forms::CheckBox());
			this->EditSun = (gcnew System::Windows::Forms::TextBox());
			this->Timer_FindGame = (gcnew System::Windows::Forms::Timer(this->components));
			this->Label_GameInfo = (gcnew System::Windows::Forms::Label());
			this->GroupAll = (gcnew System::Windows::Forms::GroupBox());
			this->GroupAll->SuspendLayout();
			this->SuspendLayout();
			// 
			// AddSun
			// 
			this->AddSun->Location = System::Drawing::Point(6, 45);
			this->AddSun->Name = L"AddSun";
			this->AddSun->Size = System::Drawing::Size(100, 23);
			this->AddSun->TabIndex = 0;
			this->AddSun->Text = L"Add Sun";
			this->AddSun->UseVisualStyleBackColor = true;
			this->AddSun->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// FreezeSun
			// 
			this->FreezeSun->AutoSize = true;
			this->FreezeSun->Location = System::Drawing::Point(124, 19);
			this->FreezeSun->Name = L"FreezeSun";
			this->FreezeSun->Size = System::Drawing::Size(72, 17);
			this->FreezeSun->TabIndex = 1;
			this->FreezeSun->Text = L"Sun 9990";
			this->FreezeSun->UseVisualStyleBackColor = true;
			this->FreezeSun->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox1_CheckedChanged);
			// 
			// NoDelay
			// 
			this->NoDelay->AutoSize = true;
			this->NoDelay->Location = System::Drawing::Point(124, 45);
			this->NoDelay->Name = L"NoDelay";
			this->NoDelay->Size = System::Drawing::Size(70, 17);
			this->NoDelay->TabIndex = 2;
			this->NoDelay->Text = L"No Delay";
			this->NoDelay->UseVisualStyleBackColor = true;
			this->NoDelay->CheckedChanged += gcnew System::EventHandler(this, &MainForm::NoDelay_CheckedChanged);
			// 
			// EditSun
			// 
			this->EditSun->Location = System::Drawing::Point(6, 19);
			this->EditSun->Name = L"EditSun";
			this->EditSun->Size = System::Drawing::Size(100, 20);
			this->EditSun->TabIndex = 3;
			this->EditSun->Text = L"1000";
			// 
			// Timer_FindGame
			// 
			this->Timer_FindGame->Enabled = true;
			this->Timer_FindGame->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// Label_GameInfo
			// 
			this->Label_GameInfo->AutoSize = true;
			this->Label_GameInfo->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->Label_GameInfo->Location = System::Drawing::Point(10, 90);
			this->Label_GameInfo->Name = L"Label_GameInfo";
			this->Label_GameInfo->Size = System::Drawing::Size(122, 13);
			this->Label_GameInfo->TabIndex = 4;
			this->Label_GameInfo->Text = L"Game não encontrado...";
			// 
			// GroupAll
			// 
			this->GroupAll->Controls->Add(this->AddSun);
			this->GroupAll->Controls->Add(this->EditSun);
			this->GroupAll->Controls->Add(this->NoDelay);
			this->GroupAll->Controls->Add(this->FreezeSun);
			this->GroupAll->Enabled = false;
			this->GroupAll->Location = System::Drawing::Point(12, 12);
			this->GroupAll->Name = L"GroupAll";
			this->GroupAll->Size = System::Drawing::Size(200, 76);
			this->GroupAll->TabIndex = 5;
			this->GroupAll->TabStop = false;
			this->GroupAll->Text = L"Úteis";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(224, 107);
			this->Controls->Add(this->GroupAll);
			this->Controls->Add(this->Label_GameInfo);
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"Hack";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->GroupAll->ResumeLayout(false);
			this->GroupAll->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		short Value = (this->FreezeSun->Checked) ? 0x9090 : 0x0A7E;
		WriteValue(0x0041F4E5, &Value, sizeof(Value));
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		int Pointer = GetPointer(0x00731C50, { 0x868,0x5578 });
		int Value = FALSE;
		ReadValue(Pointer, &Value, sizeof(Value));
		Value += int().Parse(this->EditSun->Text);
		WriteValue(Pointer, &Value, sizeof(Value));		
	}
	private: System::Void NoDelay_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		FreezeHack = !FreezeHack;
		WriteValue((DWORD)pVirtualMem, &FreezeHack, sizeof(FreezeHack));
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) 
	{
		if (GetWindowThreadProcessId(FindWindow(NULL, "Plants vs. Zombies"), &GamePID))
		{
			MainHack();
			this->Timer_FindGame->Enabled = false;
			this->GroupAll->Enabled = true;
			this->Label_GameInfo->Text = "Game Encontrado!";
			this->Label_GameInfo->ForeColor = Color().FromName("Green");
		}
	}
private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
