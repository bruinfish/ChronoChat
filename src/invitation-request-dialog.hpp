/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2013, Regents of the University of California
 *
 * BSD license, See the LICENSE file for more information
 *
 * Author: Qiuhan Ding <qiuhanding@cs.ucla.edu>
 *         Yingdi Yu <yingdi@cs.ucla.edu>
 */

#ifndef CHRONOS_INVITATION_REQUEST_DIALOG_HPP
#define CHRONOS_INVITATION_REQUEST_DIALOG_HPP

#include <QDialog>

#ifndef Q_MOC_RUN
#include "common.hpp"
#endif

namespace Ui {
class InvitationRequestDialog;
}

namespace chronos{

class InvitationRequestDialog : public QDialog
{
    Q_OBJECT

public:
  explicit
  InvitationRequestDialog(QWidget* parent = 0);

  ~InvitationRequestDialog();

signals:
  void
  invitationRequestResponded(const ndn::Name& invitationName, bool accepted);

public slots:
  void
  onInvitationRequestReceived(QString alias, QString chatroom, ndn::Name invitationInterest);

private slots:
  void
  onOkClicked();

  void
  onCancelClicked();


private:
  Ui::InvitationRequestDialog* ui;
  ndn::Name m_invitationInterest;
};

} // namespace chronos

#endif // CHRONOS_INVITATION_REQUEST_DIALOG_HPP
