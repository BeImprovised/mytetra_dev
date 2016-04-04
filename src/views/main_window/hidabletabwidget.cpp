#include "hidabletabwidget.h"
#include <QTabBar>
#include <QToolButton>

HidableTabWidget::HidableTabWidget(QWidget *parent) :
    QTabWidget(parent),
    hideAction("▾", this)
{
    hideAction.setCheckable(true);
    hideAction.setToolTip("Hide Panels");
    QToolButton *hide_button = new QToolButton();
    hide_button->setDefaultAction(&hideAction);
    hide_button->setAutoRaise(true);
    this->setCornerWidget(hide_button);


    setTabPosition(TabPosition::West); // South
    setTabShape(TabShape::Triangular);
    //    setStyleSheet("QTabBar::tab { max-width: 200px; padding: 2px; margin-left: 2px; }");
    setStyleSheet("QTabBar::tab { max-width: 200px; padding: 2px; margin-left: 2px; } QTabWidget::tab-bar { max-width: 200px; align: left; text-align: left; margin-left: 2px; padding: 2px;}");

    connect(&hideAction, &QAction::toggled, this, &HidableTabWidget::onHideAction);
    connect(this, &HidableTabWidget::tabBarClicked, this, &HidableTabWidget::onTabBarClicked);
}

void HidableTabWidget::onHideAction(bool checked)
{
    if(checked) {
        if(this->tabPosition() == North || tabPosition() == South) { // , West, East
            this->setMaximumHeight(this->tabBar()->height());
        } else {
            this->setMaximumWidth(this->tabBar()->width());
        }

        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    } else {
        if(this->tabPosition() == North || tabPosition() == South) { // , West, East
            this->setMaximumHeight(
                std::numeric_limits<int>::max() // 100000
            ); // just a very big number
            //            setContentsMargins(0, 0, 0, 0);
        } else {
            this->setMaximumWidth(
                std::numeric_limits<int>::max() // 100000
            ); // just a very big number
            //            setContentsMargins(0, 0, 0, 0);
        }

        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
}

void HidableTabWidget::onTabBarClicked()
{
    hideAction.setChecked(false);
}
