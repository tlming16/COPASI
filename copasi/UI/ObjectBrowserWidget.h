/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ObjectBrowserWidget.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: jpahle $ 
   $Date: 2004/10/07 07:41:00 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 04/03 
Comment : Copasi Object Browser: 
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef OBJECTBROWSERWIDGET_H
#define OBJECTBROWSERWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include <vector>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QListView;
class QTextEdit;
class ObjectBrowserItem;
class ObjectList;
class QListViewItem;
class QFrame;
class QSpacerItem;
class CCopasiContainer;
class CCopasiObject;
class CopasiUI3Window;

enum pageIndex {LISTVIEWPAGE = 0, SELECTEDITEMPAGE};

class ObjectBrowserWidget : public QWidget
  {
    Q_OBJECT
  private:
    pageIndex currentPage;
    std::vector<CCopasiObject*>* mOutputObjectVector;
    void selectObjects(ObjectBrowserItem* browserItem, CCopasiObject* selectObject);

  public:
    ObjectList* objectItemList;
    ObjectList* refreshList;
    ObjectBrowserWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0, int state = 0);
    ~ObjectBrowserWidget();
    void cleanup();

    QGridLayout* ObjectBrowserLayout;
    QPushButton* clearButton;
    QPushButton* toggleViewButton;
    QPushButton* commitButton;
    QListView* ObjectListView;
    QFrame* Line1;
    QSpacerItem* spacer;
    QTextEdit* ObjectItemText;

    QPixmap *pObjectAll;   // to store the image of locked icon folder
    QPixmap *pObjectParts;   // to store the image of closed icon folder
    QPixmap *pObjectNone;     // to store the image of open icon folder

    void eXport(ObjectBrowserItem* pCurrent, std::vector<CCopasiObject*>* outputVector);
    void removeDuplicate(ObjectList* objectItemList);
    void setCheck(ObjectBrowserItem* pCurrent);
    void setUncheck(ObjectBrowserItem* pCurrent);
    void clickToReverseCheck(ObjectBrowserItem* pCurrent);
    void setCheckMark(ObjectBrowserItem* pCurrent);

    void loadData();
    void loadChild(ObjectBrowserItem* parent, CCopasiContainer * copaParent, bool nField);
    void loadField(ObjectBrowserItem* parent, CCopasiContainer * copaParent);

    CCopasiObject* getFieldCopasiObject(CCopasiContainer * pCurrent, const char* name);
    void setOutputVector(std::vector<CCopasiObject*>* pObjectVector);
    void selectObjects(std::vector<CCopasiObject*>* pObjectVector);
    void updateUI();
    void loadUI();

    void swap(int, int, ObjectBrowserItem**);
    int partition(int, int, int, ObjectBrowserItem**);
    void quick_sort(int, int, ObjectBrowserItem**);

  public slots:
    virtual void clearClicked();
    virtual void toggleViewClicked();
    virtual void commitClicked();
    virtual void listviewChecked(QListViewItem*);
  };
#endif // OBJECTBROWSERWIDGET_H
