#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\SelectAction.h"
#include "Actions\LoadAction.h"
#include "Actions\ChangeBckgrndColor.h"
#include "Actions\ChangeDrawColorAction.h"
#include "Actions\ChangeFillColor.h"
#include "Actions\ChangeBorderWidthAction.h"
#include "Actions\SaveAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\CopyAction.h"
#include "Actions\CutAction.h"
#include "Actions\PasteAction.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
	ClipboardMode = 1;
	//Create an array of figure pointers and set them to NULL		
	/*for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL,
		Clipboard[i] = NULL;*/
}

void ApplicationManager::nullifyFigList() {
	while (FigCount--) {
		delete FigList[FigCount];
		FigList[FigCount] = NULL;
	}
	++FigCount;
}

bool ApplicationManager::IsFillMenu(ActionType ActType) const
{
	switch (ActType)
	{
	case ITM_BRUSHFILL_BLACK_Clicked:
		return true;
	case ITM_BRUSHFILL_BLUE_Clicked:
		return true;
	case ITM_BRUSHFILL_BROWN_Clicked:
		return true;
	case ITM_BRUSHFILL_GREEN_Clicked:
		return true;
	case ITM_BRUSHFILL_ORANGE_Clicked:
		return true;
	case ITM_BRUSHFILL_PINK_Clicked:
		return true;
	case ITM_BRUSHFILL_YELLOW_Clicked:
		return true;
	case ITM_BRUSHFILL_NILE_Clicked:
		return true;
	case ITM_BRUSHFILL_PURPLE_Clicked:
		return true;
	case ITM_BRUSHFILL_RED_Clicked:
		return true;
	}
	return false;
}
bool ApplicationManager::IsBackgroundMenu(ActionType ActType) const
{
	switch (ActType)
	{
	case ITM_BCKG_WHITE_Clicked:
		return true;
	case ITM_BCKG_BLUE_Clicked:
		return true;
	case ITM_BCKG_RED_Clicked:
		return true;
	case ITM_BCKG_PINK_Clicked:
		return true;
	case ITM_BCKG_BROWN_Clicked:
		return true;
	case ITM_BCKG_NILE_Clicked:
		return true;
	case ITM_BCKG_YELLOW_Clicked:
		return true;
	case ITM_BCKG_ORANE_Clicked:
		return true;
	case ITM_BCKG_PURPLE_Clicked:
		return true;
	case ITM_BCKG_GREEN_Clicked:
		return true;
	}
	return false;
}

bool ApplicationManager::IsPenMenu(ActionType ActType) const
{
	switch (ActType)
	{
	case ITM_BRUSH_BLACK_Clicked:
		return true;
	case ITM_BRUSH_YELLOW_Clicked:
		return true;
	case ITM_BRUSH3_BLUE_Clicked:
		return true;
	case ITM_BRUSH_BROWN_Clicked:
		return true;
	case ITM_BRUSH_PINK_Clicked:
		return true;
	case ITM_BRUSH_GREEN_Clicked:
		return true;
	case ITM_BRUSH_NILE_Clicked:
		return true;
	case ITM_BRUSH_ORANGE_Clicked:
		return true;
	case ITM_BRUSH_PURPLE_Clicked:
		return true;
	case ITM_BRUSH_RED_Clicked:
		return true;
	}
	return false;
}
//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	/*We get the user actions, we define two main types of actions,
	(1) a simple action, that's an action taken directly from an on-screen icon
	(2) a nested action, that's an action taken from a sub menu
	-for action number 1, we simple return the action type to the main
	-for action number 2, we do the following: 
	   [1] show the sub menu
	   [2] wait for the user to click an icon from the sub menu
	   [3] hide th sub menu(that includes a click in the sub menu or outside it)
	   [4] return the selected action to the main function*/

	//Ask the input to get the action from the user.
	ActionType Type = pIn->GetUserAction(), ret;
	switch (Type) {
    
	case MODE_DRAW_SUB_MENU1_Clicked:   //figures
		pOut->CreateDrawToolBarUp(1, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(figure option)
		pOut->CreateDrawToolBarUp(1, true);  //hide sub menu
		return ret;

	case MODE_DRAW_SUB_MENU2_Clicked:  //pens
		pOut->CreateDrawToolBarUp(2, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(pen option)
		pOut->CreateDrawToolBarUp(2, true);  //hide sub menu
		return ret;

	case MODE_DRAW_SUB_MENU3_Clicked: //brushes
		pOut->CreateDrawToolBarUp(3, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(brushes option)
		pOut->CreateDrawToolBarUp(3, true);  //hide sub menu
		return ret;

	case MODE_DRAW_SUB_MENU4_Clicked:  //background colors
		pOut->CreateDrawToolBarUp(4, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(background colors option)
		pOut->CreateDrawToolBarUp(4, true);  //hide sub menu
		return ret;

	case MODE_DRAW_SUB_MENU5_Clicked:  //border width
		pOut->CreateDrawToolBarUp(5, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(border width option)
		pOut->CreateDrawToolBarUp(5, true);  //hide sub menu
		return ret; 

	case ITM_RESIZE_Clicked:  //resize options
		pOut->CreateDrawToolBarUp(6, false);  //show sub menu
		ret = pIn->GetUserAction();  //get action(resize option)
		pOut->CreateDrawToolBarUp(6, true);  //hide sub menu
		return ret;
	}

	return Type;  //if not a sub menu action, return it directly.
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	//According to Action Type, create the corresponding action object
	if (IsBackgroundMenu(ActType)) {
		pAct = new ChangeBckgrndColor(this, ActType);
	}
	if (IsPenMenu(ActType)) {
		pAct = new ChangeDrawColorAction(this, ActType);
	}
	if (IsFillMenu(ActType)) {
		pAct = new ChangeFillColor(this,ActType);
	}
	/*	ITM_BORDERWIDTH1_Clicked,
	ITM_BORDERWIDTH2_Clicked,
	ITM_BORDERWIDTH3_Clicked,
	ITM_BORDERWIDTH4_Clicked,*/

	switch (ActType)
	{
		// Border Action Start
		case ITM_BORDERWIDTH1_Clicked :
			pAct = new ChangeBorderWidthAction(this,ActType);
			break;
		case ITM_BORDERWIDTH2_Clicked:
			pAct = new ChangeBorderWidthAction(this, ActType);
			break;
		case ITM_BORDERWIDTH3_Clicked:
			pAct = new ChangeBorderWidthAction(this, ActType);
			break;
		case ITM_BORDERWIDTH4_Clicked:
			pAct = new ChangeBorderWidthAction(this, ActType);
			break;
		//Border Action End
		case ITM_LOAD_Clicked:
			pAct = new LoadAction(this);
			break;
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_LINE:
			pAct = new AddLineAction(this);
			break;

		case DRAW_CIRC:
			pAct = new AddCircleAction(this);
			break;

		case DRAW_TRI:
			pAct = new AddTriangleAction(this);
			break;

		case ITM_SELECT_Clicked:
			pAct = new SelectAction(this);
			break;

		case ITM_SAVEAS_Clicked:
			pAct = new SaveAction(this);
			break;

		case EXIT:
			///create ExitAction here
			
			break;

		case ITM_DELETE_Clicked:
			pAct = new DeleteAction(this);
			break;

		case ITM_COPY_Clicked:
			pAct = new CopyAction(this);
			break;

		case ITM_CUT_Clicked:
			pAct = new CutAction(this);
			break;

		case ITM_PASTE_Clicked:
			pAct = new PasteAction(this);
			break;
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//void ApplicationManager::AddClipboard(CFigure * pFig)
//{
//	Clipboard.push_back(pFig);
//}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList.push_back(pFig);	
}

int ApplicationManager::GetFigCount() { return FigList.size(); }

int ApplicationManager::GetSelectedFigCount()
{
	int cnt = 0;
	for (int i = 0; i < FigList.size(); i++) {
		if (FigList[i]->IsSelected())
			cnt++;
	}
	return cnt;
}

void ApplicationManager::DeleteSelected(bool flag)
{
	for (int i = 0; i < FigList.size(); i++) {
		if (FigList[i]->IsSelected()) {
			if(flag) delete FigList[i];
			FigList.erase(FigList.begin() + i);
			i--;
		}
	}
}

void ApplicationManager::CutToClipboard(bool unselect)
{
	for (int i = 0; i < FigList.size(); i++) {
		if (FigList[i]->IsSelected()) {
			if (unselect) {
				FigList[i]->SetSelected(false);
				FigList[i]->ChngDrawClr(UI.DrawColor);
			}
			Clipboard.push_back(FigList[i]);
		}
	}
}

void ApplicationManager::CopyToClipboard()
{
	for (int i = 0; i < FigList.size(); i++) {
		if (FigList[i]->IsSelected()) {
			FigList[i]->SetSelected(false);
			FigList[i]->ChngDrawClr(UI.DrawColor);
			CFigure* ptr = CopyAction::CopyFigure(FigList[i]);
			Clipboard.push_back(ptr);
		}
	}
}

void ApplicationManager::AddPastedFigures(Point P)
{
	if (ClipboardMode > 1) {

		vector<CFigure*>temp(Clipboard.size());
		for (int i = 0; i < Clipboard.size(); i++)
			temp[i] = Clipboard[i];

		Clipboard.clear();
		for (int i = 0; i < temp.size(); i++) {
			CFigure* ptr = CopyAction::CopyFigure(temp[i]);
			Clipboard.push_back(ptr);
		}
	}

	for (int i = 0; i < Clipboard.size(); i++) {
		Clipboard[i]->TransferFigure(P);
		AddFigure(Clipboard[i]);
		ClipboardMode++;
	}
}

////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(int x, int y) const
{
	for (int i = FigList.size() -1; i>=0; i--) {
		if (FigList[i]->Encloses({ x,y }))  //if the point is in the figure
			return FigList[i];
	}
	return NULL;
}

//vector<CFigure*> ApplicationManager::GetSelected()
//{
//	vector<CFigure*> selected;
//	for (int i = 0; i < FigList.size(); i++) {
//		if (FigList[i]->IsSelected())
//			selected.push_back(FigList[i]);
//	}
//	return selected;
//}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigList.size(); i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}

//void ApplicationManager::UpdateFigCount(int Selected_Deleted)
//{
//	FigCount -= Selected_Deleted;
//}

void ApplicationManager::ClearClipboard()
{
	if (ClipboardMode == 1) {
		for (int i = 0; i < Clipboard.size(); i++)
			delete Clipboard[i];
	}
	Clipboard.clear();
}

int ApplicationManager::GetClipboardSize()
{
	return Clipboard.size();
}

void ApplicationManager::SaveAll(ofstream &OutFile)
{
	OutFile << FigList.size() << endl;
	for (int i = 0; i < FigList.size(); i++)
		FigList[i]->Save(OutFile);
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }

//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigList.size(); i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
}