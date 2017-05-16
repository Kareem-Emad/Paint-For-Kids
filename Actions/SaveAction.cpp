#include "SaveAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

#include <fstream>


SaveAction::SaveAction(ApplicationManager * pApp) : Action(pApp)
{
}

bool SaveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Save: Enter file name");
	FileName = pIn->GetSrting(pOut);


	pOut->ClearStatusBar();

	return true;
}

void SaveAction::Execute()
{
	ReadActionParameters();
	if (FileName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos)
	{
		pManager->GetOutput()->PrintMessage("File Name contain invalid characters");
		return;
	}
	ofstream OutFile;
	OutFile.open("Saved//" + FileName + ".txt", ios::out);
	OutFile << (int)UI.DrawColor.ucBlue << " " << (int)UI.DrawColor.ucGreen << " " << (int)UI.DrawColor.ucRed
		<< " " << endl;
	OutFile << (int)UI.FillColor.ucBlue << " " << (int)UI.FillColor.ucGreen << " " << (int)UI.FillColor.ucRed
		<< " " << endl;
	OutFile << (int)UI.BkGrndColor.ucBlue << " " << (int)UI.BkGrndColor.ucGreen 
		<< " " << (int)UI.BkGrndColor.ucRed<< " " << endl;
	pManager->SaveAll(OutFile);
	OutFile.close();
}