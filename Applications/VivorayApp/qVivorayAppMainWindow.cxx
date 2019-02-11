/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file LICENSE.  */

// Qt includes
#include <QDebug>
#include <QDesktopWidget>

// Slicer includes
#include "qSlicerAboutDialog.h"
#include "qSlicerModuleSelectorToolBar.h"
#include "qSlicerModulesMenu.h"
#include "qSlicerModuleManager.h"
#include "qSlicerAbstractModule.h"

// SlicerApp includes
#include "qVivorayAppMainWindow_p.h"
#include "qSlicerApplication.h"

//-----------------------------------------------------------------------------
// qVivorayAppMainWindowPrivate methods

qVivorayAppMainWindowPrivate::qVivorayAppMainWindowPrivate(qVivorayAppMainWindow& object)
  : Superclass(object)
{
}

//-----------------------------------------------------------------------------
qVivorayAppMainWindowPrivate::~qVivorayAppMainWindowPrivate()
{
}

//-----------------------------------------------------------------------------
void qVivorayAppMainWindowPrivate::init()
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 7, 0))
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
  Q_Q(qVivorayAppMainWindow);
  this->Superclass::init();
}

//-----------------------------------------------------------------------------
void qVivorayAppMainWindowPrivate::setupUi(QMainWindow * mainWindow)
{
  qSlicerApplication * app = qSlicerApplication::application();

  //----------------------------------------------------------------------------
  // Add actions
  //----------------------------------------------------------------------------
  QAction* helpAboutSlicerAppAction = new QAction(mainWindow);
  helpAboutSlicerAppAction->setObjectName("HelpAboutVivorayAppAction");
  helpAboutSlicerAppAction->setText("About " + app->applicationName());

  //----------------------------------------------------------------------------
  // Calling "setupUi()" after adding the actions above allows the call
  // to "QMetaObject::connectSlotsByName()" done in "setupUi()" to
  // successfully connect each slot with its corresponding action.
  this->Superclass::setupUi(mainWindow);

  //----------------------------------------------------------------------------
  // Configure
  //----------------------------------------------------------------------------
  mainWindow->setWindowIcon(QIcon(":/Icons/Medium/DesktopIcon.png"));
  QPixmap logo(":/LogoFull.png");
  this->LogoLabel->setAlignment(Qt::AlignCenter); // XXX Synx with template ?
  this->LogoLabel->setPixmap(logo);


  // To see any effect of changes over here in the application first delete the .ini file pointed by
  // --settings-path option of the project executable.

  // Hide the toolbars
  this->MainToolBar->setVisible(true);
  this->ModuleSelectorToolBar->setVisible(true);
  //this->ModuleToolBar->setVisible(false);
  //this->ViewToolBar->setVisible(false);
  //this->MouseModeToolBar->setVisible(false);
  //this->CaptureToolBar->setVisible(false);
  //this->ViewersToolBar->setVisible(false);
  this->DialogToolBar->setVisible(false);

  // Hide the menus
  //this->menubar->setVisible(false);
  //this->FileMenu->setVisible(false);
  //this->EditMenu->setVisible(false);
  //this->ViewMenu->setVisible(false);
  //this->LayoutMenu->setVisible(false);
  //this->HelpMenu->setVisible(false);

  // Hide the modules panel
  this->PanelDockWidget->setVisible(false);
  this->DataProbeCollapsibleWidget->setCollapsed(true);
  this->DataProbeCollapsibleWidget->setVisible(false);
  this->StatusBar->setVisible(false);
}

//-----------------------------------------------------------------------------
// qVivorayAppMainWindow methods

//-----------------------------------------------------------------------------
qVivorayAppMainWindow::qVivorayAppMainWindow(QWidget* windowParent)
  : Superclass(new qVivorayAppMainWindowPrivate(*this), windowParent)
{
  Q_D(qVivorayAppMainWindow);
  d->init();
}

//-----------------------------------------------------------------------------
qVivorayAppMainWindow::qVivorayAppMainWindow(
  qVivorayAppMainWindowPrivate* pimpl, QWidget* windowParent)
  : Superclass(pimpl, windowParent)
{
  // init() is called by derived class.
}

//-----------------------------------------------------------------------------
qVivorayAppMainWindow::~qVivorayAppMainWindow()
{
}

//-----------------------------------------------------------------------------
void qVivorayAppMainWindow::on_HelpAboutVivorayAppAction_triggered()
{
  qSlicerAboutDialog about(this);
  about.setLogo(QPixmap(":/Logo.png"));

  // XXX: unused, modify slicer to accept setAcknowledgmentText
  QString acknowledgmentText(
      "Supported by: NIH and the Slicer Community.<br /><br />"
      "This work is part of the  National Institute of Health grant titled "
      "<i>Shape Analysis Toolbox for Medical Image Computing Projects</i>.<br /><br />"
      "Vivoray is a  software package for medical image segmentation's "
      "shape analysis. <br /><br />"
      "Ongoing development, maintenance, distribution, and training is managed by "
      "Kitware Inc., University of North Carolina, Chapel Hill, M.D. Cancer Center "
      "at The University of Texas and NYU Tandon School of Engineering. <br /><br />");


  about.exec();
}

//-----------------------------------------------------------------------------
void qVivorayAppMainWindow::show()
{
  Q_D(qVivorayAppMainWindow);
  qSlicerModulesMenu* qMenu = d->ModuleSelectorToolBar->modulesMenu();
  qSlicerModuleManager * moduleManager = qSlicerApplication::application()->moduleManager();

  // Modules to add
  QStringList addModuleNames = QStringList()
          << "Home";
  QAction * beforeAction = qMenu->actions().at(1); // to insert after the "All Modules" menu
  foreach(const QString& moduleName, addModuleNames)
    {
    qSlicerAbstractCoreModule * coreModule = moduleManager->module(moduleName);
    qSlicerAbstractModule* module = qobject_cast<qSlicerAbstractModule*>(coreModule);
    qMenu->insertAction(beforeAction, module->action());
    }
  // Add missing separator (only if all modules removed from list)
  beforeAction = qMenu->actions().at(1);
  qMenu->insertSeparator(beforeAction);
  // Show
  this->Superclass::show();
}
