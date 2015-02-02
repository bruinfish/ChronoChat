/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2013, Regents of the University of California
 *
 * BSD license, See the LICENSE file for more information
 *
 * Author: Qiuhan Ding <qiuhanding@cs.ucla.edu>
 *         Yingdi Yu <yingdi@cs.ucla.edu>
 */

#ifndef CHRONOS_DISCOVERY_PANEL_HPP
#define CHRONOS_DISCOVERY_PANEL_HPP

#include <QDialog>
#include <QStringListModel>

#ifndef Q_MOC_RUN
#include "chatroom-info.hpp"
#endif

namespace Ui {
class DiscoveryPanel;
}

namespace chronos {

class DiscoveryPanel : public QDialog
{
  Q_OBJECT

public:
  explicit
  DiscoveryPanel(QWidget* parent = 0);

  virtual
  ~DiscoveryPanel();

private:
  void
  resetPanel();

  void
  refreshPanel();

signals:
  /**
   * @brief get chatroom info from discovery backend
   *
   * @param chatroomName the name of chatroom we want to get info from
   */
  void
  waitForChatroomInfo(const QString& chatroomName);

  /**
   * @brief send warning if strange things happen
   *
   * @param msg the message that print in the warning
   */
  void
  warning(const QString& msg);

  /**
   * @brief join the chatroom the user clicked
   *
   * This function will be called if the join button is clicked. The join button is enabled
   * when there is no trust model for the chatroom.
   * The user will join the chatroom he choose directly.
   *
   * @param chatroomName the chatroom to join
   * @param secured if security is enabled in this chatroom
   */
  void
  startChatroom(const QString& chatroomName, bool secured);

public slots:
  /**
   * @brief reset the panel when identity is updated
   *
   */
  void
  onIdentityUpdated(const QString& identity);

  /**
   * @brief print the chatroom list on the panel
   *
   * @param list list of chatroom name get from discovery backend
   */
  void
  onChatroomListReady(const QStringList& list);

  /**
   * @brief print the chatroom info on the panel
   *
   * @param info chatroom info get from discovery backend
   */
  void
  onChatroomInfoReady(const ChatroomInfo& info);

private slots:
  void
  onSelectedChatroomChanged(const QItemSelection& selected,
                     const QItemSelection& deselected);

  void
  onSelectedParticipantChanged(const QItemSelection& selected,
                                const QItemSelection& deselected);

  void
  onJoinClicked();

private:
  Ui::DiscoveryPanel* ui;

  // Models.
  QStringListModel* m_chatroomListModel;
  QStringListModel* m_rosterListModel;

  // Internal data structure.
  QStringList m_chatroomList;
  QStringList m_rosterList;
  QString     m_chatroom;
  QString     m_participant;
};

} // namespace chronos

#endif // CHRONOS_DISCOVERY_PANEL_HPP
