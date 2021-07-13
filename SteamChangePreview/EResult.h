#pragma once

#include "pch.h"

const char* GetEResultName(EResult eResult) {
	switch (eResult) {
	case k_EResultOK: return "k_EResultOK";
	case k_EResultFail: return "k_EResultFail";
	case k_EResultNoConnection: return "k_EResultNoConnection";
	case k_EResultInvalidPassword: return "k_EResultInvalidPassword";
	case k_EResultLoggedInElsewhere: return "k_EResultLoggedInElsewhere";
	case k_EResultInvalidProtocolVer: return "k_EResultInvalidProtocolVer";
	case k_EResultInvalidParam: return "k_EResultInvalidParam";
	case k_EResultFileNotFound: return "k_EResultFileNotFound";
	case k_EResultBusy: return "k_EResultBusy";
	case k_EResultInvalidState: return "k_EResultInvalidState";
	case k_EResultInvalidName: return "k_EResultInvalidName";
	case k_EResultInvalidEmail: return "k_EResultInvalidEmail";
	case k_EResultDuplicateName: return "k_EResultDuplicateName";
	case k_EResultAccessDenied: return "k_EResultAccessDenied";
	case k_EResultTimeout: return "k_EResultTimeout";
	case k_EResultBanned: return "k_EResultBanned";
	case k_EResultAccountNotFound: return "k_EResultAccountNotFound";
	case k_EResultInvalidSteamID: return "k_EResultInvalidSteamID";
	case k_EResultServiceUnavailable: return "k_EResultServiceUnavailable";
	case k_EResultNotLoggedOn: return "k_EResultNotLoggedOn";
	case k_EResultPending: return "k_EResultPending";
	case k_EResultEncryptionFailure: return "k_EResultEncryptionFailure";
	case k_EResultInsufficientPrivilege: return "k_EResultInsufficientPrivilege";
	case k_EResultLimitExceeded: return "k_EResultLimitExceeded";
	case k_EResultRevoked: return "k_EResultRevoked";
	case k_EResultExpired: return "k_EResultExpired";
	case k_EResultAlreadyRedeemed: return "k_EResultAlreadyRedeemed";
	case k_EResultDuplicateRequest: return "k_EResultDuplicateRequest";
	case k_EResultAlreadyOwned: return "k_EResultAlreadyOwned";
	case k_EResultIPNotFound: return "k_EResultIPNotFound";
	case k_EResultPersistFailed: return "k_EResultPersistFailed";
	case k_EResultLockingFailed: return "k_EResultLockingFailed";
	case k_EResultLogonSessionReplaced: return "k_EResultLogonSessionReplaced";
	case k_EResultConnectFailed: return "k_EResultConnectFailed";
	case k_EResultHandshakeFailed: return "k_EResultHandshakeFailed";
	case k_EResultIOFailure: return "k_EResultIOFailure";
	case k_EResultRemoteDisconnect: return "k_EResultRemoteDisconnect";
	case k_EResultShoppingCartNotFound: return "k_EResultShoppingCartNotFound";
	case k_EResultBlocked: return "k_EResultBlocked";
	case k_EResultIgnored: return "k_EResultIgnored";
	case k_EResultNoMatch: return "k_EResultNoMatch";
	case k_EResultAccountDisabled: return "k_EResultAccountDisabled";
	case k_EResultServiceReadOnly: return "k_EResultServiceReadOnly";
	case k_EResultAccountNotFeatured: return "k_EResultAccountNotFeatured";
	case k_EResultAdministratorOK: return "k_EResultAdministratorOK";
	case k_EResultContentVersion: return "k_EResultContentVersion";
	case k_EResultTryAnotherCM: return "k_EResultTryAnotherCM";
	case k_EResultPasswordRequiredToKickSession: return "k_EResultPasswordRequiredToKickSession";
	case k_EResultAlreadyLoggedInElsewhere: return "k_EResultAlreadyLoggedInElsewhere";
	case k_EResultSuspended: return "k_EResultSuspended";
	case k_EResultCancelled: return "k_EResultCancelled";
	case k_EResultDataCorruption: return "k_EResultDataCorruption";
	case k_EResultDiskFull: return "k_EResultDiskFull";
	case k_EResultRemoteCallFailed: return "k_EResultRemoteCallFailed";
	case k_EResultPasswordUnset: return "k_EResultPasswordUnset";
	case k_EResultExternalAccountUnlinked: return "k_EResultExternalAccountUnlinked";
	case k_EResultPSNTicketInvalid: return "k_EResultPSNTicketInvalid";
	case k_EResultExternalAccountAlreadyLinked: return "k_EResultExternalAccountAlreadyLinked";
	case k_EResultRemoteFileConflict: return "k_EResultRemoteFileConflict";
	case k_EResultIllegalPassword: return "k_EResultIllegalPassword";
	case k_EResultSameAsPreviousValue: return "k_EResultSameAsPreviousValue";
	case k_EResultAccountLogonDenied: return "k_EResultAccountLogonDenied";
	case k_EResultCannotUseOldPassword: return "k_EResultCannotUseOldPassword";
	case k_EResultInvalidLoginAuthCode: return "k_EResultInvalidLoginAuthCode";
	case k_EResultAccountLogonDeniedNoMail: return "k_EResultAccountLogonDeniedNoMail";
	case k_EResultHardwareNotCapableOfIPT: return "k_EResultHardwareNotCapableOfIPT";
	case k_EResultIPTInitError: return "k_EResultIPTInitError";
	case k_EResultParentalControlRestricted: return "k_EResultParentalControlRestricted";
	case k_EResultFacebookQueryError: return "k_EResultFacebookQueryError";
	case k_EResultExpiredLoginAuthCode: return "k_EResultExpiredLoginAuthCode";
	case k_EResultIPLoginRestrictionFailed: return "k_EResultIPLoginRestrictionFailed";
	case k_EResultAccountLockedDown: return "k_EResultAccountLockedDown";
	case k_EResultAccountLogonDeniedVerifiedEmailRequired: return "k_EResultAccountLogonDeniedVerifiedEmailRequired";
	case k_EResultNoMatchingURL: return "k_EResultNoMatchingURL";
	case k_EResultBadResponse: return "k_EResultBadResponse";
	case k_EResultRequirePasswordReEntry: return "k_EResultRequirePasswordReEntry";
	case k_EResultValueOutOfRange: return "k_EResultValueOutOfRange";
	case k_EResultUnexpectedError: return "k_EResultUnexpectedError";
	case k_EResultDisabled: return "k_EResultDisabled";
	case k_EResultInvalidCEGSubmission: return "k_EResultInvalidCEGSubmission";
	case k_EResultRestrictedDevice: return "k_EResultRestrictedDevice";
	case k_EResultRegionLocked: return "k_EResultRegionLocked";
	case k_EResultRateLimitExceeded: return "k_EResultRateLimitExceeded";
	case k_EResultAccountLoginDeniedNeedTwoFactor: return "k_EResultAccountLoginDeniedNeedTwoFactor";
	case k_EResultItemDeleted: return "k_EResultItemDeleted";
	case k_EResultAccountLoginDeniedThrottle: return "k_EResultAccountLoginDeniedThrottle";
	case k_EResultTwoFactorCodeMismatch: return "k_EResultTwoFactorCodeMismatch";
	case k_EResultTwoFactorActivationCodeMismatch: return "k_EResultTwoFactorActivationCodeMismatch";
	case k_EResultAccountAssociatedToMultiplePartners: return "k_EResultAccountAssociatedToMultiplePartners";
	case k_EResultNotModified: return "k_EResultNotModified";
	case k_EResultNoMobileDevice: return "k_EResultNoMobileDevice";
	case k_EResultTimeNotSynced: return "k_EResultTimeNotSynced";
	case k_EResultSmsCodeFailed: return "k_EResultSmsCodeFailed";
	case k_EResultAccountLimitExceeded: return "k_EResultAccountLimitExceeded";
	case k_EResultAccountActivityLimitExceeded: return "k_EResultAccountActivityLimitExceeded";
	case k_EResultPhoneActivityLimitExceeded: return "k_EResultPhoneActivityLimitExceeded";
	case k_EResultRefundToWallet: return "k_EResultRefundToWallet";
	case k_EResultEmailSendFailure: return "k_EResultEmailSendFailure";
	case k_EResultNotSettled: return "k_EResultNotSettled";
	case k_EResultNeedCaptcha: return "k_EResultNeedCaptcha";
	case k_EResultGSLTDenied: return "k_EResultGSLTDenied";
	case k_EResultGSOwnerDenied: return "k_EResultGSOwnerDenied";
	case k_EResultInvalidItemType: return "k_EResultInvalidItemType";
	case k_EResultIPBanned: return "k_EResultIPBanned";
	case k_EResultGSLTExpired: return "k_EResultGSLTExpired";
	case k_EResultInsufficientFunds: return "k_EResultInsufficientFunds";
	case k_EResultTooManyPending: return "k_EResultTooManyPending";
	default: return "k_EResultNone";
	}
}

const char* GetEResultDescription(EResult eResult) {
	switch (eResult) {
	case k_EResultOK: return "Success.";
	case k_EResultFail: return "Generic failure.";
	case k_EResultNoConnection: return "Your Steam client doesn't have a connection to the back-end.";
	case k_EResultInvalidPassword: return "Password/ticket is invalid.";
	case k_EResultLoggedInElsewhere: return "The user is logged in elsewhere.";
	case k_EResultInvalidProtocolVer: return "Protocol version is incorrect.";
	case k_EResultInvalidParam: return "A parameter is incorrect.";
	case k_EResultFileNotFound: return "File was not found.";
	case k_EResultBusy: return "Called method is busy - action not taken.";
	case k_EResultInvalidState: return "Called object was in an invalid state.";
	case k_EResultInvalidName: return "The name was invalid.";
	case k_EResultInvalidEmail: return "The email was invalid.";
	case k_EResultDuplicateName: return "The name is not unique.";
	case k_EResultAccessDenied: return "Access is denied.";
	case k_EResultTimeout: return "Operation timed out.";
	case k_EResultBanned: return "The user is VAC2 banned.";
	case k_EResultAccountNotFound: return "Account not found.";
	case k_EResultInvalidSteamID: return "The Steam ID was invalid.";
	case k_EResultServiceUnavailable: return "The requested service is currently unavailable.";
	case k_EResultNotLoggedOn: return "The user is not logged on.";
	case k_EResultPending: return "Request is pending, it may be in process or waiting on third party.";
	case k_EResultEncryptionFailure: return "Encryption or Decryption failed.";
	case k_EResultInsufficientPrivilege: return "Insufficient privilege.";
	case k_EResultLimitExceeded: return "Too much of a good thing.";
	case k_EResultRevoked: return "Access has been revoked (used for revoked guest passes.)";
	case k_EResultExpired: return "License/Guest pass the user is trying to access is expired.";
	case k_EResultAlreadyRedeemed: return "Guest pass has already been redeemed by account, cannot be used again.";
	case k_EResultDuplicateRequest: return "The request is a duplicate and the action has already occurred in the past, ignored this time.";
	case k_EResultAlreadyOwned: return "All the games in this guest pass redemption request are already owned by the user.";
	case k_EResultIPNotFound: return "IP address not found.";
	case k_EResultPersistFailed: return "Failed to write change to the data store.";
	case k_EResultLockingFailed: return "Failed to acquire access lock for this operation.";
	case k_EResultLogonSessionReplaced: return "The logon session has been replaced.";
	case k_EResultConnectFailed: return "Failed to connect.";
	case k_EResultHandshakeFailed: return "The authentication handshake has failed.";
	case k_EResultIOFailure: return "There has been a generic IO failure.";
	case k_EResultRemoteDisconnect: return "The remote server has disconnected.";
	case k_EResultShoppingCartNotFound: return "Failed to find the shopping cart requested.";
	case k_EResultBlocked: return "A user blocked the action.";
	case k_EResultIgnored: return "The target is ignoring sender.";
	case k_EResultNoMatch: return "Nothing matching the request found.";
	case k_EResultAccountDisabled: return "The account is disabled.";
	case k_EResultServiceReadOnly: return "This service is not accepting content changes right now.";
	case k_EResultAccountNotFeatured: return "Account doesn't have value, so this feature isn't available.";
	case k_EResultAdministratorOK: return "Allowed to take this action, but only because requester is admin.";
	case k_EResultContentVersion: return "A Version mismatch in content transmitted within the Steam protocol.";
	case k_EResultTryAnotherCM: return "The current CM can't service the user making a request, user should try another.";
	case k_EResultPasswordRequiredToKickSession: return "You are already logged in elsewhere, this cached credential login has failed.";
	case k_EResultAlreadyLoggedInElsewhere: return "The user is logged in elsewhere. (Use k_EResultLoggedInElsewhere instead!)";
	case k_EResultSuspended: return "Long running operation has suspended/paused. (eg. content download.)";
	case k_EResultCancelled: return "Operation has been canceled, typically by user. (eg. a content download.)";
	case k_EResultDataCorruption: return "Operation canceled because data is ill formed or unrecoverable.";
	case k_EResultDiskFull: return "Operation canceled - not enough disk space.";
	case k_EResultRemoteCallFailed: return "The remote or IPC call has failed.";
	case k_EResultPasswordUnset: return "Password could not be verified as it's unset server side.";
	case k_EResultExternalAccountUnlinked: return "External account (PSN, Facebook...) is not linked to a Steam account.";
	case k_EResultPSNTicketInvalid: return "PSN ticket was invalid.";
	case k_EResultExternalAccountAlreadyLinked: return "External account (PSN, Facebook...) is already linked to some other account, must explicitly request to replace/delete the link first.";
	case k_EResultRemoteFileConflict: return "The sync cannot resume due to a conflict between the local and remote files.";
	case k_EResultIllegalPassword: return "The requested new password is not allowed.";
	case k_EResultSameAsPreviousValue: return "New value is the same as the old one. This is used for secret question and answer.";
	case k_EResultAccountLogonDenied: return "Account login denied due to 2nd factor authentication failure.";
	case k_EResultCannotUseOldPassword: return "The requested new password is not legal.";
	case k_EResultInvalidLoginAuthCode: return "Account login denied due to auth code invalid.";
	case k_EResultAccountLogonDeniedNoMail: return "Account login denied due to 2nd factor auth failure - and no mail has been sent.";
	case k_EResultHardwareNotCapableOfIPT: return "The users hardware does not support Intel's Identity Protection Technology (IPT).";
	case k_EResultIPTInitError: return "Intel's Identity Protection Technology (IPT) has failed to initialize.";
	case k_EResultParentalControlRestricted: return "Operation failed due to parental control restrictions for current user.";
	case k_EResultFacebookQueryError: return "Facebook query returned an error.";
	case k_EResultExpiredLoginAuthCode: return "Account login denied due to an expired auth code.";
	case k_EResultIPLoginRestrictionFailed: return "The login failed due to an IP restriction.";
	case k_EResultAccountLockedDown: return "The current users account is currently locked for use. This is likely due to a hijacking and pending ownership verification.";
	case k_EResultAccountLogonDeniedVerifiedEmailRequired: return "The logon failed because the accounts email is not verified.";
	case k_EResultNoMatchingURL: return "There is no URL matching the provided values.";
	case k_EResultBadResponse: return "Bad Response due to a Parse failure, missing field, etc.";
	case k_EResultRequirePasswordReEntry: return "The user cannot complete the action until they re-enter their password.";
	case k_EResultValueOutOfRange: return "The value entered is outside the acceptable range.";
	case k_EResultUnexpectedError: return "Something happened that we didn't expect to ever happen.";
	case k_EResultDisabled: return "The requested service has been configured to be unavailable.";
	case k_EResultInvalidCEGSubmission: return "The files submitted to the CEG server are not valid.";
	case k_EResultRestrictedDevice: return "The device being used is not allowed to perform this action.";
	case k_EResultRegionLocked: return "The action could not be complete because it is region restricted.";
	case k_EResultRateLimitExceeded: return "Temporary rate limit exceeded, try again later, different from k_EResultLimitExceeded which may be permanent.";
	case k_EResultAccountLoginDeniedNeedTwoFactor: return "Need two-factor code to login.";
	case k_EResultItemDeleted: return "The thing we're trying to access has been deleted.";
	case k_EResultAccountLoginDeniedThrottle: return "Login attempt failed, try to throttle response to possible attacker.";
	case k_EResultTwoFactorCodeMismatch: return "Two factor authentication (Steam Guard) code is incorrect.";
	case k_EResultTwoFactorActivationCodeMismatch: return "The activation code for two-factor authentication (Steam Guard) didn't match.";
	case k_EResultAccountAssociatedToMultiplePartners: return "The current account has been associated with multiple partners.";
	case k_EResultNotModified: return "The data has not been modified.";
	case k_EResultNoMobileDevice: return "The account does not have a mobile device associated with it.";
	case k_EResultTimeNotSynced: return "The time presented is out of range or tolerance.";
	case k_EResultSmsCodeFailed: return "SMS code failure - no match, none pending, etc.";
	case k_EResultAccountLimitExceeded: return "Too many accounts access this resource.";
	case k_EResultAccountActivityLimitExceeded: return "Too many changes to this account.";
	case k_EResultPhoneActivityLimitExceeded: return "Too many changes to this phone.";
	case k_EResultRefundToWallet: return "Cannot refund to payment method, must use wallet.";
	case k_EResultEmailSendFailure: return "Cannot send an email.";
	case k_EResultNotSettled: return "Can't perform operation until payment has settled.";
	case k_EResultNeedCaptcha: return "The user needs to provide a valid captcha.";
	case k_EResultGSLTDenied: return "A game server login token owned by this token's owner has been banned.";
	case k_EResultGSOwnerDenied: return "Game server owner is denied for some other reason such as account locked, community ban, vac ban, missing phone, etc.";
	case k_EResultInvalidItemType: return "The type of thing we were requested to act on is invalid.";
	case k_EResultIPBanned: return "The IP address has been banned from taking this action.";
	case k_EResultGSLTExpired: return "This Game Server Login Token (GSLT) has expired from disuse; it can be reset for use.";
	case k_EResultInsufficientFunds: return "user doesn't have enough wallet funds to complete the action";
	case k_EResultTooManyPending: return "There are too many of this thing pending already";
	default: return "k_EResultNone";
	}
}