#include "Output.h"


Output::Output()
{
	/*Initialize user interface parameters*/
	UI.InterfaceMode = MODE_DRAW;

	/*Setting the dimensions of the application window*/
	UI.width = 1500; //Setting the width of the window.
	UI.height = 800; //Setting the height of the window.
	UI.wx = 5;  //Setting the starting position of the window.
	UI.wy = 5;   //Setting the ending position on the window.

	/*Setting the dimensions of the toolbars right,up,left*/
	UI.StatusBarHeight = 80;      //Settting the height of the status bar.
	UI.MenuItemWidthLeft = 50;    //Setting the width of icons in the left menu.
	UI.MenuItemWidthUp = 100;     //Setting the width of icons in the upper menu.
	UI.MenuItemWidthRight = 60;   //Setting the width of icons in the right menu.
	UI.MenuItemHeight = 60;
	/*Setting the default colors for drawing and window background*/
	UI.DrawColor = BLUE;	//Setting the drawing color of figures.
	UI.FillColor = GREEN;	//Setting the filling color of the figures.
	UI.MsgColor = RED;		//Setting the color of the messages displayed on the status bar.
	UI.BkGrndColor = WHITE;	//Setting the background color.
	UI.HighlightColor = MAGENTA;	//Setting the highlighting color.
	UI.StatusBarColor = TURQUOISE;  //Setting the color of the status bar.
	UI.PenWidth = 3;	//Setting the width of figures frames.

	/*Ceating the output window and setting the new name for the app*/
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	/*Drawing all four menus for the application window*/
	CreateDrawToolBarLeft(false);
	CreateDrawToolBarUp();
	CreateDrawToolBarRight(false);

	/*Drawing the status bar in the application window*/
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);  //Background.
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBarRight(bool collapse) const
{
	UI.InterfaceMode = MODE_DRAW;  //Setting the current mode.

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem

	
	/*Adding two parallel icons for zooming in and out*/;
	string zoomControls[CounterZoom];
	zoomControls[ITM_ZOOM_IN] = "images\\MenuItems\\ICONS\\TOOLS\\ZOOMIN.jpg";
	zoomControls[ITM_ZOOM_OUT] = "images\\MenuItems\\ICONS\\TOOLS\\ZOOMOUT.jpg";
	pWind->DrawImage(zoomControls[ITM_ZOOM_IN], 1385, 13 * 50, 50, 50);
	pWind->DrawImage(zoomControls[ITM_ZOOM_OUT], 1435, 13 * 50, 50, 50);


	/*Loading the icons for the left toolbar.*/
	string MenuItemImages[DRAW_ITM_COUNT_LEFT];
	MenuItemImages[ITM_COLLAPSERIGHT] = "images\\MenuItems\\ICONS\\TOOLS\\COLLAPSE.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\ICONS\\TOOLS\\LOAD.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\ICONS\\TOOLS\\MOVE.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\ICONS\\TOOLS\\SELECT.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\ICONS\\TOOLS\\RESIZE1.jpg";
	MenuItemImages[ITM_COPY] = "images\\MenuItems\\ICONS\\TOOLS\\COPY.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\ICONS\\TOOLS\\CUT.jpg";
	MenuItemImages[ITM_PASTE] = "images\\MenuItems\\ICONS\\TOOLS\\PASTE.jpg";
	MenuItemImages[ITM_REDO] = "images\\MenuItems\\ICONS\\TOOLS\\REDO11.jpg";
	MenuItemImages[ITM_UNDO] = "images\\MenuItems\\ICONS\\TOOLS\\UNDO11.jpg";
	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\ICONS\\TOOLS\\DELETE.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\ICONS\\TOOLS\\SAVE.jpg";
	MenuItemImages[ITM_SAVEAS] = "images\\MenuItems\\ICONS\\TOOLS\\SAVEAS.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\ICONS\\TOOLS\\EXIT.jpg";

	if (!collapse) {
		//Drawing the left toolbar, excluding the last three icons(not needed now)
		for (int i = 1; i < DRAW_ITM_COUNT_LEFT - 2; i++)
			pWind->DrawImage(MenuItemImages[i], 1435, i*50, UI.MenuItemWidthLeft, UI.MenuItemWidthLeft);
	}
	else {
		pWind->SetBrush(UI.BkGrndColor);
		pWind->SetPen(UI.BkGrndColor, 1);
		for (int j = 0; j < 80; j++) {
			//Drawing the left toolbar, excluding the last three icons(not needed now)
			for (int i = 1; i < DRAW_ITM_COUNT_LEFT - 2; i++) {
				pWind->DrawImage(MenuItemImages[i], 1435 + (0.7)*j, i*50, UI.MenuItemWidthLeft, UI.MenuItemWidthLeft);
				pWind->DrawRectangle(1435, 50, 1435 + (0.7)*j, 600);
			}
		}
	}
	pWind->DrawImage(MenuItemImages[ITM_COLLAPSERIGHT], 1385, 0, UI.MenuItemWidthLeft, UI.MenuItemWidthLeft);
	pWind->DrawImage(MenuItemImages[ITM_EXIT], 1435, 0, UI.MenuItemWidthLeft, UI.MenuItemWidthLeft);

}


void Output::CreateDrawToolBarLeft(bool collapse) const
{
	UI.InterfaceMode = MODE_DRAW;   //Setting the current mode.

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem

	/*Here we draw two menus side-by-side, the first menu contains brush
	colors the control the draw color of the outerline of a figure, the second
	menu shows the fill colors to control the fill color of a figure*/

	//Collapse the GAME_MODE UPPER toolbar.
	
	pWind->SetBrush(UI.BkGrndColor);
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->DrawRectangle(0, 0, PLAY_ITM_COUNT * 100, 100);


	string UPPERRIGHTICONS[2];
	UPPERRIGHTICONS[0] = "images\\MenuItems\\ICONS\\COLLAPSE.jpg";
	UPPERRIGHTICONS[1] = "images\\MenuItems\\ICONS\\JOYSTICK.jpg";

	pWind->DrawImage(UPPERRIGHTICONS[0], 60, 0, 60, 60);
	pWind->DrawImage(UPPERRIGHTICONS[1], 0, 0, 60, UI.MenuItemHeight);


	//Loading the icons for the first menu of the right toolbar.
	string MenuItemImages1[DRAW_ITEM_COUNT_RIGHTBRUSH];
	MenuItemImages1[ITM_BRUSH1] = "images\\MenuItems\\ICONS\\COLOR-RED.jpg";
	MenuItemImages1[ITM_BRUSH2] = "images\\MenuItems\\ICONS\\COLOR-GREEN.jpg";
	MenuItemImages1[ITM_BRUSH3] = "images\\MenuItems\\ICONS\\COLOR-YELLOW.jpg";
	MenuItemImages1[ITM_BRUSH4] = "images\\MenuItems\\ICONS\\COLOR-ORANGE.jpg";
	MenuItemImages1[ITM_BRUSH5] = "images\\MenuItems\\ICONS\\COLOR-NILE.jpg";
	MenuItemImages1[ITM_BRUSH6] = "images\\MenuItems\\ICONS\\COLOR-BROWN.jpg";
	MenuItemImages1[ITM_BRUSH7] = "images\\MenuItems\\ICONS\\COLOR-LAST.jpg";
	MenuItemImages1[ITM_BRUSH8] = "images\\MenuItems\\ICONS\\COLOR-BLUE.jpg";
	MenuItemImages1[ITM_BRUSH9] = "images\\MenuItems\\ICONS\\COLOR-PURBLE.jpg";
	MenuItemImages1[ITM_BRUSH10] = "images\\MenuItems\\ICONS\\COLOR-BLACK.jpg";
	MenuItemImages1[ITM_COLLAPSELEFT] = "images\\MenuItems\\ICONS\\COLLAPSE.jpg";
	
	if (!collapse) {
		//Drawing the icons for the first menu of the right toolbar.
		for (int i = 0; i < DRAW_ITEM_COUNT_RIGHTBRUSH - 1; i++) // 1 here is the intializer of enum 
			pWind->DrawImage(MenuItemImages1[i], 0, ((i + 1) * 60), 120, UI.MenuItemHeight);
	}
	else {
		pWind->SetBrush(UI.BkGrndColor);
		pWind->SetPen(UI.BkGrndColor, 1);
		for (int j = 0; j < 120; j++) {
			for (int i = 0; i < DRAW_ITEM_COUNT_RIGHTBRUSH - 1; i++) { // 1 here is the intializer of enum 
				pWind->DrawImage(MenuItemImages1[i], -(j*1.5), ((i + 1) * 60), 120, UI.MenuItemHeight);
				pWind->DrawRectangle(120, 60, 120-(j*1.5), 602);
			}
		}
	}

	////Loading the icons for the second menu of the right toolbar.
	//string playModeIcon = "images\\MenuItems\\ICONS\\JOYSTICK.jpg";
	//pWind->DrawImage(playModeIcon, 60, 600, UI.MenuItemHeight, UI.MenuItemHeight);

}


void Output::CreateDrawToolBarUp() const
{
	UI.InterfaceMode = MODE_DRAW;   //Setting the current mode.

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem

	//Loading the icons for the upper toolbar.
	string MenuItemImages[DRAW_ITEM_COUNT_UP];
	MenuItemImages[ITM_CIRCLE] = "images\\MenuItems\\ICONS\\CIRCULE.jpg";
	MenuItemImages[ITM_RECTANGLE] = "images\\MenuItems\\ICONS\\RECTANGLE.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\MenuItems\\ICONS\\TRIANGLE.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\ICONS\\LINE.jpg";

	//Drawing the upper toolbar.
	for (int i = 5; i<DRAW_ITEM_COUNT_UP; i++)
		pWind->DrawImage(MenuItemImages[i], 500 + (i - 5)*UI.MenuItemWidthUp, 0, UI.MenuItemWidthUp, UI.MenuItemWidthUp);
}


//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;

	//Collapse the left toolbar.
	pWind->SetBrush(UI.BkGrndColor);
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->DrawRectangle(0, 0, 120, 660);

	//Collapse the upper toolbar.
	pWind->DrawRectangle(500, 0, 900, 100);

	
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_SCRAMBLE] = "images\\MenuItems\\ICONS\\TOOLS\\SCRAMBLE.jpg";
	MenuItemImages[ITM_FIND] = "images\\MenuItems\\ICONS\\TOOLS\\FIND.jpg";
	MenuItemImages[ITEM_TODRAW] = "images\\MenuItems\\ICONS\\TOOLS\\TODRAW1.jpg";

	for (int i = 0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], 500 + (i - 5)*UI.MenuItemWidthUp, 0, UI.MenuItemWidthUp, UI.MenuItemWidthUp);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(120, 100, UI.width - 115, UI.height - UI.StatusBarHeight);
	//I changed the clear function to only clear the area enclosed by all 4 toolbars
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
}

void Output::DrawLine(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	
	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y,FRAME);
}

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void Output::DrawCircle(Point center, int radius, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawCircle(center.x, center.y, radius, style);
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}