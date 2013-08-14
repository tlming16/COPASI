#ifndef CQ_SPRING_LAYOUT_PARAMETER_WINDOW_H
#define CQ_SPRING_LAYOUT_PARAMETER_WINDOW_H

#include <qdockwidget.h>
#include <QString>
#include <vector>

#include <layout/CCopasiSpringLayout.h>

class QwtSlider;
class CQSpringLayoutParameterWindow : public QDockWidget
{
  Q_OBJECT
public: 
  CQSpringLayoutParameterWindow(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
  virtual ~CQSpringLayoutParameterWindow();
  CCopasiSpringLayout::Parameters& getLayoutParameters();

protected slots:
    void slotLayoutSliderChanged();
protected:
  std::vector<QwtSlider*> mLayoutSliders;
  CCopasiSpringLayout::Parameters mLayoutParameters;
};

#endif