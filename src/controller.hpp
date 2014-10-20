/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2013, Regents of the University of California
 *                     Yingdi Yu
 *
 * BSD license, See the LICENSE file for more information
 *
 * Author: Yingdi Yu <yingdi@cs.ucla.edu>
 */

#ifndef CHRONOS_CONTROLLER_HPP
#define CHRONOS_CONTROLLER_HPP

#include <QDialog>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QtSql/QSqlDatabase>

#include "setting-dialog.hpp"
#include "start-chat-dialog.hpp"
#include "profile-editor.hpp"
#include "invitation-dialog.hpp"
#include "contact-panel.hpp"
#include "browse-contact-dialog.hpp"
#include "add-contact-panel.hpp"
#include "chat-dialog.hpp"

#ifndef Q_MOC_RUN
#include "common.hpp"
#include "invitation.hpp"
#include "controller-backend.hpp"
#endif

namespace chronos {

class Controller : public QDialog
{
  Q_OBJECT

public: // public methods
  Controller(QWidget* parent = 0);

  virtual
  ~Controller();

private: // private methods
  std::string
  getDBName();

  void
  openDB();

  void
  initialize();

  void
  loadConf();

  void
  saveConf();

  void
  createActions();

  void
  createTrayIcon();

  void
  updateMenu();

  std::string
  getRandomString();

  void
  addChatDialog(const QString& chatroomName, ChatDialog* chatDialog);

  void
  updateDiscoveryList(const chronos::ChatroomInfo& chatroomName, bool isAdd);

signals:
  void
  shutdownBackend();

  void
  updateLocalPrefix();

  void
  closeDBModule();

  void
  localPrefixUpdated(const QString& localPrefix);

  void
  localPrefixConfigured(const QString& prefix);

  void
  identityUpdated(const QString& identity);

  void
  refreshBrowseContact();

  void
  invitationInterest(const ndn::Name& prefix, const ndn::Interest& interest,
                     size_t routingPrefixOffset);

  void
  discoverChatroomChanged(const chronos::ChatroomInfo& chatroomInfo, bool isAdd);

  void
  addChatroom(QString chatroomName);

  void
  removeChatroom(QString chatroomName);

private slots:
  void
  onIdentityUpdated(const QString& identity);

  void
  onIdentityUpdatedContinued();

  void
  onNickUpdated(const QString& nick);

  void
  onLocalPrefixUpdated(const QString& localPrefix);

  void
  onLocalPrefixConfigured(const QString& prefix);

  void
  onStartChatAction();

  void
  onDiscoveryAction();

  void
  onSettingsAction();

  void
  onProfileEditorAction();

  void
  onAddContactAction();

  void
  onContactListAction();

  void
  onDirectAdd();

  void
  onMinimizeAction();

  void
  onQuitAction();

  void
  onStartChatroom(const QString& chatroom, bool secured);

  void
  onStartChatroom2(chronos::Invitation invitation, bool secured);

  void
  onShowChatMessage(const QString& chatroomName, const QString& from, const QString& data);

  void
  onResetIcon();

  void
  onRemoveChatDialog(const QString& chatroom);

  void
  onWarning(const QString& msg);

  void
  onError(const QString& msg);

  void
  onRosterChanged(const chronos::ChatroomInfo& info);

private: // private member
  typedef std::map<std::string, QAction*> ChatActionList;
  typedef std::map<std::string, ChatDialog*> ChatDialogList;

  // Communication
  Name m_localPrefix;
  bool m_localPrefixDetected;

  // Tray
  QAction*         m_startChatroom;
  QAction*         m_discoveryAction;
  QAction*         m_minimizeAction;
  QAction*         m_settingsAction;
  QAction*         m_editProfileAction;
  QAction*         m_contactListAction;
  QAction*         m_addContactAction;
  QAction*         m_updateLocalPrefixAction;
  QAction*         m_quitAction;
  QMenu*           m_trayIconMenu;
  QMenu*           m_closeMenu;
  QSystemTrayIcon* m_trayIcon;
  ChatActionList   m_chatActionList;
  ChatActionList   m_closeActionList;

  // Dialogs
  SettingDialog*       m_settingDialog;
  StartChatDialog*     m_startChatDialog;
  ProfileEditor*       m_profileEditor;
  InvitationDialog*    m_invitationDialog;
  ContactPanel*        m_contactPanel;
  BrowseContactDialog* m_browseContactDialog;
  AddContactPanel*     m_addContactPanel;
  ChatDialogList       m_chatDialogList;

  // Conf
  Name m_identity;
  std::string m_nick;
  QSqlDatabase m_db;

  // Backend
  ControllerBackend m_backend;
};

} // namespace chronos

#endif //CHRONOS_CONTROLLER_HPP
