# `core:auth`
`core:auth` is a system responsible for authentication and authorization.

## Extensions
- `core:res_to` - ID of the request the system is responding to.
- `core:auth:type` - Message type.
  - Inbound
    - [`pass_auth`](#pass_auth) 
  - Outbound
    - `err` - error 
    - [`pass_auth_response`](#pass_auth_response)
    - [`pass_auth_rejection`](#pass_auth_rejection)

## Message types

### Inbound

#### `pass_auth`
Request an authentication token for a given user, authenticating with a password.

##### Required extensions
- `core:auth:user_handle` - User handle.
- `core:auth:pass_auth:password` - User password.

#### `drop_token`
Invalidate an authentication token.

##### Required extensions
- `core:auth:token` - Authentication token.

### Outbound

#### `pass_auth_response`
Success response to `pass_auth`.

##### Extensions
- `core:auth:token` - Authentication token.

#### `pass_auth_rejection`
Failure response to `pass_auth`

##### Extensions
- `core:auth:pass_auth_rejection:cause` - Rejection cause.
