/****************************************************************************
**  $ CopasiUI/copasiui3window.h                 Modified on : 8th March, 2002
**  $ Author  : Ankur Gupta
**  
**  
**   
**
*****************************************************************************/

#include <qmainwindow.h>
#include <qtoolbar.h>

#include "copasi.h"
#include "listviews.h"




#include "./icons/fileopen.xpm"
#include "./icons/filesave.xpm"
#include "./icons/fileprint.xpm"


class ListViews;
class CopasiUI3Window : public QMainWindow
{
	Q_OBJECT
public:
	CopasiUI3Window( QWidget* parent = 0, const char* name = 0, WFlags f = WType_TopLevel );

protected:


	DataModel<Folder>* dataModel; // to keep track of the data model..
    QSplitter *splitter;// to hold different views...
	ListViews *listViews; // to create different list views...
	CModel mModel;
protected slots:
	void slotFileOpen();
	void slotFileSave();
	void slotFileSaveAs();
	void newDoc();
	void slotFilePrint();
	void about();  // added by ankur on 5th feb 2002
    void aboutQt(); // added by ankur on 5th feb 2002
private: // added by ankur on 5th feb 2002
	void createToolBar();
	void createMenuBar();
	

};

