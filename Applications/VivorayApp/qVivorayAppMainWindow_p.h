/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file LICENSE.  */

#ifndef __qVivorayAppMainWindow_p_h
#define __qVivorayAppMainWindow_p_h

// Vivoray includes
#include "qVivorayAppMainWindow.h"

// Slicer includes
#include "qSlicerMainWindow_p.h"

//-----------------------------------------------------------------------------
class Q_VIVORAY_APP_EXPORT qVivorayAppMainWindowPrivate
  : public qSlicerMainWindowPrivate
{
  Q_DECLARE_PUBLIC(qVivorayAppMainWindow);
public:
  typedef qSlicerMainWindowPrivate Superclass;
  qVivorayAppMainWindowPrivate(qVivorayAppMainWindow& object);
  virtual ~qVivorayAppMainWindowPrivate();

  virtual void init();
  /// Reimplemented for custom behavior
  virtual void setupUi(QMainWindow * mainWindow);
};

#endif
