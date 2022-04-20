/*
 *
 * Copyright (c) Microsoft Corporation.
 * All rights reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
/**
 * @brief Defines ProtectionEngine interface
 * 
 * @file protection_engine.h
 */

#ifndef API_MIP_PROTECTION_PROTECTION_ENGINE_H_
#define API_MIP_PROTECTION_PROTECTION_ENGINE_H_

#include <memory>
#include <string>
#include <vector>

#include "mip/common_types.h"
#include "mip/mip_namespace.h"
#include "mip/protection_descriptor.h"
#include "mip/protection/delegation_license.h"
#include "mip/protection/delegation_license_settings.h"
#include "mip/protection/protection_common_types.h"
#include "mip/protection/protection_handler.h"
#include "mip/protection/template_descriptor.h"

MIP_NAMESPACE_BEGIN

/**
 * @brief Manages protection-related actions related to a specific identity
 */
class ProtectionEngine {
public:
  /**
   * @brief Interface that receives notifications related to ProtectionEngine
   * 
   * @note This interface must be implemented by applications using the protection SDK
   */
  class Observer {
  public:
    /**
     * @brief Called when templates were retrieved successfully
     *
     * @param templateDescriptors A reference to the list of templates descriptors
     * @param context The same context that was passed to ProtectionEngine::GetTemplatesAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::GetTemplatesAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnGetTemplatesSuccess or ProtectionEngine::Observer::OnGetTemplatesFailure
     */
    virtual void OnGetTemplatesSuccess(
        const std::vector<std::shared_ptr<TemplateDescriptor>>& templateDescriptors,
        const std::shared_ptr<void>& context) { UNUSED(templateDescriptors); UNUSED(context); }

    /**
     * @brief Called when retrieving templates generated an error
     *
     * @param error Error that occurred while retrieving templates
     * @param context The same context that was passed to ProtectionEngine::GetTemplatesAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::GetTemplatesAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnGetTemplatesSuccess or ProtectionEngine::Observer::OnGetTemplatesFailure
     */
    virtual void OnGetTemplatesFailure(
        const std::exception_ptr& error,
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when rights were retrieved successfully
     *
     * @param rights A reference to the list of rights retrieved
     * @param context The same context that was passed to ProtectionEngine::GetRightsForLabelIdAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::GetRightsForLabelIdAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnGetRightsForLabelIdSuccess or ProtectionEngine::Observer::OnGetRightsForLabelIdFailure
     */
    virtual void OnGetRightsForLabelIdSuccess(
        const std::shared_ptr<std::vector<std::string>>& rights,
        const std::shared_ptr<void>& context) { UNUSED(rights); UNUSED(context); }

    /**
     * @brief Called when retrieving rights for a label ID for the user
     *
     * @param error Error that occurred while retrieving rights
     * @param context The same context that was passed to ProtectionEngine::GetRightsForLabelIdAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::GetRightsForLabelIdAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnGetRightsForLabelIdSuccess or ProtectionEngine::Observer::OnGetRightsForLabelIdFailure
     */
    virtual void OnGetRightsForLabelIdFailure(
        const std::exception_ptr& error,
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }
    
    /**
     * @brief Called when user cert loaded successfully
     *
     * @param context The same context that was passed to ProtectionEngine::LoadUserCert
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::LoadUserCertAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnLoadUserCertSuccess or ProtectionEngine::Observer::OnLoadUserCertFailure
     */
    virtual void OnLoadUserCertSuccess(
        const std::shared_ptr<void>& context) { UNUSED(context); }

    /**
     * @brief Called when user cert loaded failed
     *
     * @param error Error that occurred while retrieving rights
     * @param context The same context that was passed to ProtectionEngine::LoadUserCert
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::LoadUserCertAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnLoadUserCertSuccess or ProtectionEngine::Observer::OnLoadUserCertFailure
     */
    virtual void OnLoadUserCertFailure(
        const std::exception_ptr& error,
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when registration of content for tracking & revocation is successful
     *
     * @param context The same context that was passed to ProtectionEngine::RegisterContentForTrackingAndRevocationAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::RegisterContentForTrackingAndRevocationAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnRegisterContentForTrackingAndRevocationSuccess or ProtectionEngine::Observer::OnRegisterContentForTrackingAndRevocationFailure
     */
    virtual void OnRegisterContentForTrackingAndRevocationSuccess(
        const std::shared_ptr<void>& context) { UNUSED(context); }

    /**
     * @brief Called when registration of content for tracking & revocation fails
     *
     * @param error Error that occurred while registering content
     * @param context The same context that was passed to ProtectionEngine::RegisterContentForTrackingAndRevocationAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::RegisterContentForTrackingAndRevocationAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnRegisterContentForTrackingAndRevocationSuccess or ProtectionEngine::Observer::OnRegisterContentForTrackingAndRevocationFailure
     */
    virtual void OnRegisterContentForTrackingAndRevocationFailure(
        const std::exception_ptr& error,
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when revocation of is successful
     *
     * @param context The same context that was passed to ProtectionEngine::RevokeContentAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::RevokeContentAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnRevokeContentSuccess or ProtectionEngine::Observer::OnRevokeContentFailure
     */
    virtual void OnRevokeContentSuccess(
        const std::shared_ptr<void>& context) { UNUSED(context); }

    /**
     * @brief Called when revocation of content is fails
     *
     * @param error Error that occurred while revoking content
     * @param context The same context that was passed to ProtectionEngine::RevokeContentAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::RevokeContentAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnRevokeContentSuccess or ProtectionEngine::Observer::OnRevokeContentFailure
     */
    virtual void OnRevokeContentFailure(
        const std::exception_ptr& error,
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }

    /**
     * @brief Called when create delegated license is successful
     *
     * @param context The same context that was passed to ProtectionEngine::CreateDelegationLicensesAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::CreateDelegationLicensesAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnCreateDelegatedLicensesSuccess or ProtectionEngine::Observer::OnCreateDelegatedLicensesFailure
     */
    virtual void OnCreateDelegatedLicensesSuccess(
        std::vector<std::shared_ptr<DelegationLicense>> delegatedLicenses,
        const std::shared_ptr<void>& context) { UNUSED(delegatedLicenses); UNUSED(context); }

    /**
     * @brief Called when create delegated license fails
     *
     * @param error Error that occurred
     * @param context The same context that was passed to ProtectionEngine::CreateDelegationLicensesAsync
     *
     * @note An application can pass any type of context (for example, std::promise, std::function) to
     * ProtectionEngine::CreateDelegationLicensesAsync and that same context will be forwarded as-is to
     * ProtectionEngine::Observer::OnCreateDelegatedLicensesSuccess or ProtectionEngine::Observer::OnCreateDelegatedLicensesFailure
     */
    virtual void OnCreateDelegatedLicensesFailure(
        const std::exception_ptr& error,
        const std::shared_ptr<void>& context) { UNUSED(error); UNUSED(context); }
    
    /** @cond DOXYGEN_HIDE */
    virtual ~Observer() { }
  protected:
    Observer() { }
    /** @endcond */
  };
  
  /**
   * @brief Settings used by ProtectionEngine during its creation and throughout its lifetime
   */
  class Settings {
  public:
    /**
     * @brief ProtectionEngine::Settings constructor for creating a new engine
     * 
     * @param identity Identity that will be associated with ProtectionEngine
     * @param authDelegate The authentication delegate used by the SDK to acquire authentication tokens, will override the 
     * PolicyProfile::Settings::authDelegate if both provided
     * @param clientData customizable client data that can be stored with the engine when unloaded and can be retrieved
     * from a loaded engine.
     * @param locale Engine output will be provided in this locale.
     * 
     */
    Settings(
        const Identity& identity,
        const std::shared_ptr<AuthDelegate>& authDelegate,
        const std::string& clientData,
        const std::string& locale = "en-US" )
        : mIdentity(identity),
          mAuthDelegate(authDelegate),
          mClientData(clientData),
          mLocale(locale),
          mAllowCloudServiceOnly(false) {
    }

    /**
     * @brief ProtectionEngine::Settings constructor for loading an existing engine
     * 
     * @param engineId Unique identifier of engine that will be loaded
     * @param authDelegate The authentication delegate used by the SDK to acquire authentication tokens, will override the 
     * PolicyProfile::Settings::authDelegate if both provided
     * @param clientData customizable client data that can be stored with the engine when unloaded and can be retrieved
     * from a loaded engine.
     * @param locale Engine output will be provided in this locale.
     * 
     */
    Settings(
        const std::string& engineId,
        const std::shared_ptr<AuthDelegate>& authDelegate,
        const std::string& clientData,
        const std::string& locale = "en-US" )
        : mEngineId(engineId),
          mAuthDelegate(authDelegate),
          mClientData(clientData),
          mLocale(locale),
          mAllowCloudServiceOnly(false) {
    }

    /**
     * @brief Gets the engine ID.
     * 
     * @return Engine ID
     */
    const std::string& GetEngineId() const { return mEngineId; }

    /**
     * @brief Sets the engine ID.
     * 
     * @param engineId engine ID.
     */
    void SetEngineId(const std::string& engineId) { mEngineId = engineId; }

    /**
     * @brief Gets the user Identity associated with the engine
     * 
     * @return User Identity associated with the engine
     */
    const Identity& GetIdentity() const { return mIdentity; }

    /**
     * @brief Sets the user Identity associated with the engine
     * 
     * @param identity User Identity associated with the engine
     */
    void SetIdentity(const Identity& identity) { mIdentity = identity; }

    /**
     * @brief Gets custom data specified by client
     * 
     * @return Custom data specified by client
     */
    const std::string& GetClientData() const { return mClientData; }

    /**
     * @brief Sets custom data specified by client
     * 
     * @param Custom data specified by client
     */
    void SetClientData(const std::string& clientData) { mClientData = clientData; }

    /**
     * @brief Gets the locale in which engine data will be written
     * 
     * @return Locale in which engine data will be written
     */
    const std::string& GetLocale() const { return mLocale; }

    /**
     * @brief Sets name/value pairs used for testing and experimentation
     * 
     * @param customSettings Name/value pairs used for testing and experimentation
     */
    void SetCustomSettings(const std::vector<std::pair<std::string, std::string>>& value) { mCustomSettings = value; }

    /**
     * @brief Gets name/value pairs used for testing and experimentation
     * 
     * @return Name/value pairs used for testing and experimentation
     */
    const std::vector<std::pair<std::string, std::string>>& GetCustomSettings() const { return mCustomSettings; }

    /**
    * @brief Sets the engine session ID, used for correlation of logging/telemetry
    * 
    * @param sessionId Engine session ID, used for correlation of logging/telemetry
    */
    void SetSessionId(const std::string& sessionId) {
      mSessionId = sessionId;
    }

    /**
    * @brief Gets the engine session ID
    * 
    * @return Engine session ID
    */
    const std::string& GetSessionId() const {
      return mSessionId;
    }

    /**
    * @brief Optionally sets the target cloud
    * 
    * @param Cloud Cloud
    * 
    * @note If cloud is not specified, then it will be determined by DNS lookup of the engine's
    *       identity domain if possible, else fall back to global cloud.
    */
    void SetCloud(Cloud cloud) {
      mCloud = cloud;
    }

    /**
    * @brief Gets the target cloud used by all service requests
    * 
    * @return cloud
    */
    Cloud GetCloud() const {
      return mCloud;
    }

    /**
    * @brief Sets the cloud endpoint base URL for custom cloud
    * 
    * @param cloudEndpointBaseUrl the base URL used by all service requests (for example, "https://api.aadrm.com")
    * 
    * @note This value will only be read and must be set for Cloud = Custom
    */
    void SetCloudEndpointBaseUrl(const std::string& cloudEndpointBaseUrl) {
      mCloudEndpointBaseUrl = cloudEndpointBaseUrl;
    }

    /**
    * @brief Gets the cloud base URL used by all service requests, if specified
    * 
    * @return base URL
    */
    const std::string& GetCloudEndpointBaseUrl() const {
      return mCloudEndpointBaseUrl;
    }

    /**
     * @brief Set the Engine Auth Delegate.
     * 
     * @param authDelegate the Auth delegate
     */
    void SetAuthDelegate(const std::shared_ptr<AuthDelegate>& authDelegate) { 
      mAuthDelegate = authDelegate; 
    }

    /**
     * @brief Get the Engine Auth Delegate.
     * 
     * @return the Engine Auth Delegate. 
     */
    std::shared_ptr<AuthDelegate> GetAuthDelegate() const { return mAuthDelegate; }

    /**
     * @brief Gets the Underlying Application ID.
     *
     * @return Underlying Application ID
     */
    const std::string& GetUnderlyingApplicationId() const { return mUnderlyingApplicationId; }

    /**
     * @brief Sets the Underlying Application ID.
     *
     * @param UnderlyingApplicationId Underlying Application ID.
     */
    void SetUnderlyingApplicationId(const std::string& underlyingApplicationId) { mUnderlyingApplicationId = underlyingApplicationId; }

    /**
     * @brief Gets whether or not only cloud service is allowed
     *
     * @return A boolean value indicating whether or not only cloud service is allowed
     */
    bool GetAllowCloudServiceOnly() const { return mAllowCloudServiceOnly; }

    /**
     * @brief Sets whether or not only cloud service is allowed
     *
     * @param allowCloudServiceOnly A boolean value indicating whether or not only cloud service is allowed
     */
    void SetAllowCloudServiceOnly(bool allowCloudServiceOnly) { mAllowCloudServiceOnly = allowCloudServiceOnly; }
    
  /** @cond DOXYGEN_HIDE */
  private:
    std::string mEngineId;
    Identity mIdentity;
    Cloud mCloud = Cloud::Unknown;
    std::shared_ptr<AuthDelegate> mAuthDelegate;
    std::string mClientData;
    std::vector<std::pair<std::string, std::string>> mCustomSettings;
    std::string mCloudEndpointBaseUrl;
    std::string mLocale;
    std::string mSessionId;
    std::string mUnderlyingApplicationId;
    bool mAllowCloudServiceOnly;
  /** @endcond */
  };

  /**
   * @brief Gets the engine settings
   * 
   * @return Engine settings
   */
  virtual const Settings& GetSettings() const = 0;

  /**
   * @brief Get collection of templates available to a user
   *
   * @param observer A class implementing the ProtectionEngine::Observer interface
   * @param context Client context that will be opaquely passed back to observers and optional HttpDelegate
   * @return Async control object.
   */
  virtual std::shared_ptr<AsyncControl> GetTemplatesAsync(
      const std::shared_ptr<ProtectionEngine::Observer>& observer,
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Get collection of templates available to a user
   *
   * @param context Client context that will be opaquely passed to optional HttpDelegate
   * 
   * @return List of template IDs
   */
  virtual std::vector<std::shared_ptr<TemplateDescriptor>> GetTemplates(const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Check is feature supported
   *
   * @param featureId id of feature to check
   * 
   * @return boolean result
   */
  virtual bool IsFeatureSupported(FeatureId featureId) = 0;

  /**
   * @brief Get collection of rights available to a user for a label ID
   *
   * @param documentId Document ID associated with the document metadata
   * @param labelId Label ID associated with the document metadata with which the document created
   * @param ownerEmail owner of the document
   * @param A delegated user is specified when the authenticating user/application is acting on behalf of another user, empty if none
   * @param observer A class implementing the ProtectionEngine::Observer interface
   * @param context This same context will be forwarded to ProtectionEngine::Observer::OnGetRightsForLabelIdSuccess
   * or ProtectionEngine::Observer::OnGetRightsForLabelIdFailure
   * @return Async control object.
   */
  virtual std::shared_ptr<AsyncControl> GetRightsForLabelIdAsync(
      const std::string& documentId,
      const std::string& labelId,
      const std::string& ownerEmail,
      const std::string& delegatedUserEmail,
      const std::shared_ptr<ProtectionEngine::Observer>& observer,
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Get collection of rights available to a user for a labelId
   *
   * @param documentId Document ID associated with the document metadata
   * @param labelId Label ID associated with the document metadata with which the document created
   * @param ownerEmail Owner of the document
   * @param A delegated user is specified when the authenticating user/application is acting on behalf of another user, empty if none
   * @param context This same context will be forwarded to optional HttpDelegate
   * 
   * @return List of rights
   */
  virtual std::vector<std::string> GetRightsForLabelId(
      const std::string& documentId,
      const std::string& labelId,
      const std::string& ownerEmail,
      const std::string& delegatedUserEmail,
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Creates a protection handler where rights/roles are assigned to specific users
   * 
   * @param settings Protection settings
   * @param observer A class implementing the ProtectionHandler::Observer interface
   * @param context Client context that will be opaquely forwarded to observers and optional HttpDelegate
   * @return Async control object.
   */
  virtual std::shared_ptr<AsyncControl> CreateProtectionHandlerForPublishingAsync(
      const ProtectionHandler::PublishingSettings& settings,
      const std::shared_ptr<ProtectionHandler::Observer>& observer,
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Creates a protection handler where rights/roles are assigned to specific users
   * 
   * @param settings Protection settings
   * @param context Client context that will be opaquely forwarded to optional HttpDelegate
   * 
   * @return ProtectionHandler
   */
  virtual std::shared_ptr<ProtectionHandler> CreateProtectionHandlerForPublishing(
      const ProtectionHandler::PublishingSettings& settings,
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Creates a protection handler where rights/roles are assigned to specific users
   * 
   * @param settings Protection settings
   * @param observer A class implementing the ProtectionHandler::Observer interface
   * @param context Client context that will be opaquely forwarded to observers and optional HttpDelegate
   * @return Async control object.
   */
  virtual std::shared_ptr<AsyncControl> CreateProtectionHandlerForConsumptionAsync(
      const ProtectionHandler::ConsumptionSettings& settings,
      const std::shared_ptr<ProtectionHandler::Observer>& observer,
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Creates a protection handler where rights/roles are assigned to specific users
   * 
   * @param settings Protection settings
   * @param context Client context that will be opaquely forwarded to optional HttpDelegate
   * 
   * @return ProtectionHandler
   */
  virtual std::shared_ptr<ProtectionHandler> CreateProtectionHandlerForConsumption(
      const ProtectionHandler::ConsumptionSettings& settings,
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief pre-emptively load user licensor certificate, useful when background loading else using prelicense might
   * incurr an additional network call.
   * 
   * @param context Client context that will be opaquely forwarded to optional HttpDelegate
   * 
   * @return true if loaded successfully else false.
   */
  virtual bool LoadUserCert(
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief pre-emptively load user licensor certificate, useful when background loading else using prelicense might
   * incurr an additional network call.
   * 
   * @param observer A class implementing the ProtectionHandler::Observer interface
   * @param context Client context that will be opaquely forwarded to observers and optional HttpDelegate
   * @return Async control object.
   */
  virtual std::shared_ptr<AsyncControl> LoadUserCertAsync(
      const std::shared_ptr<ProtectionEngine::Observer>& observer,
      const std::shared_ptr<void>& context) = 0;

/**
   * @brief Register publishing license (PL) for document tracking & revocation
   * 
   * @param contentName The name to associated with the content specified by the serializedPublishingLicense. If the serializedPublishingLicense specifies a content name, that value will take precedence.
   * @param isOwnerNotificationEnabled Set to true to notify the owner via email whenever the document is decrypted, or false to not send the notification.
   * @param context Client context that will be opaquely forwarded to optional HttpDelegate
   */
  virtual void RegisterContentForTrackingAndRevocation(
    const std::vector<uint8_t>& serializedPublishingLicense,
    const std::string& contentName,
    bool isOwnerNotificationEnabled,
    const std::shared_ptr<void>& context) = 0;

    /**
   * @brief Register publishing license (PL) for document tracking & revocation
   * 
   * @param serializedPublishingLicense Serialized publishing license from protected content
   * @param contentName The name to associated with the content specified by the serializedPublishingLicense. If the serializedPublishingLicense specifies a content name, that value will take precedence
   * @param isOwnerNotificationEnabled Set to true to notify the owner via email whenever the document is decrypted, or false to not send the notification.
   * @param observer A class implementing the ProtectionHandler::Observer interface
   * @param context Client context that will be opaquely forwarded to observers and optional HttpDelegate
   * 
   * @return Async control object.
   */
  virtual std::shared_ptr<AsyncControl> RegisterContentForTrackingAndRevocationAsync(
    const std::vector<uint8_t>& serializedPublishingLicense,
    const std::string& contentName,
    bool isOwnerNotificationEnabled,
    const std::shared_ptr<ProtectionEngine::Observer>& observer,
    const std::shared_ptr<void>& context) = 0;

/**
   * @brief Perform revocation for content
   * 
   * @param serializedPublishingLicense Serialized publishing license from protected content
   * @param context Client context that will be opaquely forwarded to optional HttpDelegate
   */
  virtual void RevokeContent(
    const std::vector<uint8_t>& serializedPublishingLicense,
    const std::shared_ptr<void>& context) = 0;

/**
   * @brief Perform revocation for content
   * 
   * @param serializedPublishingLicense Serialized publishing license from protected content
   * @param observer A class implementing the ProtectionHandler::Observer interface
   * @param context Client context that will be opaquely forwarded to observers and optional HttpDelegate
   * 
   * @return Async control object.
   */
  virtual std::shared_ptr<AsyncControl> RevokeContentAsync(
    const std::vector<uint8_t>& serializedPublishingLicense,
    const std::shared_ptr<ProtectionEngine::Observer>& observer,
    const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Creates a delegated license
   * 
   * @param settings The delegation settings
   * @param context Client context that will be opaquely forwarded to observers and optional HttpDelegate
   * @return A vector of the delegation licenses
   * 
   * @note Use this method to create licenses for a list of users
   */
  virtual std::vector<std::shared_ptr<DelegationLicense>> CreateDelegationLicenses(
      const DelegationLicenseSettings& settings,
      const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Creates a delegated license
   * 
   * @param settings The delegation settings
   * @param observer A class implementing the ProtectionHandler::Observer interface
   * @param context Client context that will be opaquely forwarded to observers and optional HttpDelegate
   * @return Async control object.
   * 
   * @note Use this method to create licenses for a list of users.
   *       Receive the DelegationLicense vector in callback OnCreateDelegatedLicensesSuccess
   *       Failures are sent in OnCreateDelegatedLicensesFailure
   */
  virtual std::shared_ptr<AsyncControl> CreateDelegationLicensesAsync(
      const DelegationLicenseSettings& settings,
      const std::shared_ptr<ProtectionEngine::Observer>& observer,
      const std::shared_ptr<void>& context) = 0;

  /** @cond DOXYGEN_HIDE */
  virtual ~ProtectionEngine() {}
protected:
  ProtectionEngine() {}
  /** @endcond */
};

MIP_NAMESPACE_END

#endif // API_MIP_PROTECTION_PROTECTION_ENGINE_H_
