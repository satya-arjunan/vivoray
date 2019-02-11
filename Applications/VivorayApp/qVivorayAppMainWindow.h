/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file LICENSE.  */

#ifndef __qVivorayAppMainWindow_h
#define __qVivorayAppMainWindow_h

// Vivoray includes
#include "qVivorayAppExport.h"
class qVivorayAppMainWindowPrivate;

// Slicer includes
#include "qSlicerMainWindow.h"

class Q_VIVORAY_APP_EXPORT qVivorayAppMainWindow : public qSlicerMainWindow
{
  Q_OBJECT
public:
  typedef qSlicerMainWindow Superclass;

  qVivorayAppMainWindow(QWidget *parent=0);
  virtual ~qVivorayAppMainWindow();

public:
  virtual void show();

public slots:
  void on_HelpAboutVivorayAppAction_triggered();

protected:
  qVivorayAppMainWindow(qVivorayAppMainWindowPrivate* pimpl, QWidget* parent);

private:
  Q_DECLARE_PRIVATE(qVivorayAppMainWindow);
  Q_DISABLE_COPY(qVivorayAppMainWindow);
};

#endif
