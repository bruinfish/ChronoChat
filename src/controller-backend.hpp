/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2013, Regents of the University of California
 *
 * BSD license, See the LICENSE file for more information
 *
 * Author: Yingdi Yu <yingdi@cs.ucla.edu>
 */

#ifndef CHRONOCHAT_CONTROLLER_BACKEND_HPP
#define CHRONOCHAT_CONTROLLER_BACKEND_HPP

#include <QString>
#include <QThread>
#include <QStringList>
#include <QMutex>

#ifndef Q_MOC_RUN
#include "common.hpp"
#include "contact-manager.hpp"
#include "invitation.hpp"
#include "validator-invitation.hpp"
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/util/in-memory-storage-persistent.hpp>
#endif

namespace chronos {

class ControllerBackend : public QThread
{
  Q_OBJECT

public:
  ControllerBackend(QObject* parent = 0);

  ~ControllerBackend();

  ContactManager*
  getContactManager()
  {
    return &m_contactManager;
  }

protected:
  void
  run();

private:
  void
  setInvitationListener();

  ndn::Name
  getInvitationRoutingPrefix();

  void
  onInvitationPrefixReset();

  void
  onInvitationPrefixResetFailed(const std::string& failInfo);

  void
  onInvitationInterest(const ndn::Name& prefix, const ndn::Interest& interest,
                       size_t routingPrefixOffset);

  void
  onInvitationRequestInterest(const ndn::Name& prefix, const ndn::Interest& interest,
                              size_t routingPrefixOffset);

  void
  onInvitationRegisterFailed(const Name& prefix, const std::string& failInfo);

  void
  onInvitationValidated(const shared_ptr<const Interest>& interest);

  void
  onInvitationValidationFailed(const shared_ptr<const Interest>& interest,
                               std::string failureInfo);

  void
  onLocalPrefix(const Interest& interest, Data& data);

  void
  onLocalPrefixTimeout(const Interest& interest);

  void
  updateLocalPrefix(const Name& localPrefix);

  void
  onRequestResponse(const Interest& interest, Data& data);

  void
  onRequestTimeout(const Interest& interest, int& resendTimes);

signals:
  void
  identityUpdated(const QString& identity);

  void
  localPrefixUpdated(const QString& localPrefix);

  void
  invitationValidated(QString alias, QString chatroom, ndn::Name invitationINterest);

  void
  invitationRequestReceived(QString alias, QString chatroom, ndn::Name invitationRequestInterest);

  void
  startChatroomOnInvitation(chronos::Invitation invitation, bool secured);

  void
  startChatroom(const QString& chatroomName, bool secured);

  void
  invitationRequestResult(const std::string& msg);

public slots:
  void
  shutdown();

  void
  addChatroom(QString chatroom);

  void
  removeChatroom(QString chatroom);

  void
  onUpdateLocalPrefixAction();

  void
  onIdentityChanged(const QString& identity);

  void
  onInvitationResponded(const ndn::Name& invitationName, bool accepted);

  void
  onInvitationRequestResponded(const ndn::Name& invitationName, bool accepted);

  void
  onSendInvitationRequest(const QString& chatroomName, const QString& prefix);

private slots:
  void
  onContactIdListReady(const QStringList& list);

private:
  ndn::Face m_face;

  Name m_identity;  //TODO: set/get

  Name m_localPrefix;

  // Contact Manager
  ContactManager m_contactManager;

  // Security related;
  ndn::KeyChain m_keyChain;
  ValidatorInvitation m_validator;

  // RegisteredPrefixId
  const ndn::RegisteredPrefixId* m_invitationListenerId;
  const ndn::RegisteredPrefixId* m_requestListenerId;

  // ChatRoomList
  QStringList m_chatDialogList;

  QMutex m_mutex;

  ndn::util::InMemoryStoragePersistent m_ims;
};

} // namespace chronos

#endif // CHRONOCHAT_CONTROLLER_BACKEND_HPP
