#pragma once

class AuthProviderResult {
public:
    enum class FailureType {
        UserNotFound, BadPassword, Forbidden, Other
    };
private:
    bool is_success;
    FailureType failure;
    AuthProviderResult() {};
public:
    static AuthProviderResult success() {
        AuthProviderResult result;
        result.is_success = true;
        return result;
    }

    static AuthProviderResult failure(FailureType f) {
        AuthProviderResult result;
        result.is_success = false;
        result.failure = f;
        return result;
    }

    bool get_is_success() {
        return this->is_success;
    }

    FailureType get_failure() {
        return this->failure;
    }
};

class IAuthProvider {
public:
    virtual ~IAuthProvider() {}
    virtual AuthProviderResult authenticate(ChatHandle user, std::string password) = 0;
};