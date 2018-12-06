// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef MEASUREMENT_KIT_MKCURL_H
#define MEASUREMENT_KIT_MKCURL_H

/// @file mkcurl.h
///
/// This file contains Measurement Kit cURL wrappers. You should create a
/// mkcurl_request_t instance and configure it. Make sure you supply the URL
/// otherwise we don't know what to do. Then you can perform the request by
/// using mkcurl_request_perform_nonnull. This function returns the response as a
/// mkcurl_response_t instance. Make sure you check whether there was any
/// sort of network level error with mkcurl_response_get_error_v2, and also
/// check the HTTP status code with mkcurl_response_get_status_code_v2 to
/// be sure your request succeded before proceeding further. In case of error
/// you can always inspect the logs. Be careful that the logs may contain
/// non UTF-8 data, hence on some languages you cannot treat them as a string.

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/// mkcurl_request_t is an HTTP request.
typedef struct mkcurl_request mkcurl_request_t;

/// mkcurl_response_t is an HTTP response.
typedef struct mkcurl_response mkcurl_response_t;

/// mkcurl_request_new_nonnull creates a new request object. This function
/// calls abort if allocating a new request fails.
mkcurl_request_t *mkcurl_request_new_nonnull(void);

/// mkcurl_request_set_ca_bundle_path_v2 sets the CA bundle path. Typically
/// this option is required on mobile devices. This function calls abort
/// if passed null arguments by the caller.
void mkcurl_request_set_ca_bundle_path_v2(mkcurl_request_t *req, const char *p);

/// mkcurl_request_enable_http2_v2 enables using the HTTP2 protocol. If the
/// HTTP2 backend is not compiled in, the mkcurl_request_perform_nonnull will
/// fail when trying to use it. This function calls abort if passed a
/// null argument by the caller.
void mkcurl_request_enable_http2_v2(mkcurl_request_t *req);

/// mkcurl_request_set_method_post_v2 sets the method to POST (default is GET).
/// It calls abort if passed a null argument by the caller.
void mkcurl_request_set_method_post_v2(mkcurl_request_t *req);

/// mkcurl_request_set_method_put_v2 sets the method to PUT (default is GET). It
/// calls abort if passed a null argument by the caller.
void mkcurl_request_set_method_put_v2(mkcurl_request_t *req);

/// mkcurl_request_set_url_v2 sets the request URL. This setting is required
/// otherwise we will not know what to do. This function calls abort
/// if it is passed any null argument by the caller.
void mkcurl_request_set_url_v2(mkcurl_request_t *req, const char *u);

/// mkcurl_request_add_header_v2 adds an header to the request. This function
/// calls abort if it is passed any null argument by the caller.
void mkcurl_request_add_header_v2(mkcurl_request_t *req, const char *h);

/// mkcurl_request_set_body_binary_v3 sets the body as a binary vector. This
/// function calls abort if it is passed any null argument by the caller.
void mkcurl_request_set_body_binary_v3(mkcurl_request_t *req,
                                       const uint8_t *b, size_t n);

/// mkcurl_request_set_timeout_v2 sets the timeout. That is, the time after
/// which the request/response handling loop is interrupted. Setting zero or a
/// negative value tells CURL to disable such timeout. By default, we configure
/// CURL using a small, but reasonable timeout. This function calls abort
/// if passed a null pointer by the caller. The maximum timeout value that
/// you can actually set is LONG_MAX. Any value bigger than that will be treated
/// as you actually passed LONG_MAX to this function.
void mkcurl_request_set_timeout_v2(mkcurl_request_t *req, int64_t timeout);

/// mkcurl_request_set_proxy_url_v2 sets the proxy URL. To use Tor, set
/// this option to `socks5h://127.0.0.1:9050`. This function calls abort
/// if passed any null pointer argument by the caller.
void mkcurl_request_set_proxy_url_v2(mkcurl_request_t *req, const char *u);

/// mkcurl_request_enable_follow_redirect_v2 enables following redirects. This
/// function call abort if passed any null argument by the caller.
void mkcurl_request_enable_follow_redirect_v2(mkcurl_request_t *req);

/// mkcurl_request_enable_tcp_fastopen enables TCP fastopen (if that is
/// possible). This function will call abort if @p req is null.
void mkcurl_request_enable_tcp_fastopen(mkcurl_request_t *req);

/// mkcurl_request_set_connect_to allows to override the IP address to
/// connect to. The hostname specified in the URL will still be used for
/// SNI if TLS is to be used. This function will abort if passed
/// any null pointer argument by the caller. This functionality is exposed
/// such that OONI can perform its own DNS resolution in some cases.
void mkcurl_request_set_connect_to(mkcurl_request_t *req, const char *ip);

/// mkcurl_request_perform_nonnull sends an HTTP request and returns the related
/// response. It will never return a null pointer. It will call abort if
/// passed a null argument by the caller.
mkcurl_response_t *mkcurl_request_perform_nonnull(const mkcurl_request_t *req);

/// mkcurl_request_delete deletes @p req. Note that @p req MAY be null.
void mkcurl_request_delete(mkcurl_request_t *req);

/// mkcurl_response_get_error_v2 returns the CURL error that occurred. Remember
/// the the request MAY have failed even though no error occurred (i.e. you
/// SHOULD also check the status code). This function will call abort if
/// passed a null pointer argument by the caller.
int64_t mkcurl_response_get_error_v2(const mkcurl_response_t *res);

/// mkcurl_response_get_redirect_url_v2 returns the URL to which we were
/// redirected, if redirection is enabled, otherwise returns an empty string.
/// This function calls abort if passed a null argument.
const char *mkcurl_response_get_redirect_url_v2(const mkcurl_response_t *res);

/// mkcurl_response_get_status_code_v2 returns the status code. This function
/// calls abort if passed a null pointer by the caller.
int64_t mkcurl_response_get_status_code_v2(const mkcurl_response_t *res);

/// mkcurl_response_get_body_binary_v3 returns the body as a binary vector. It
/// calls abort if passed a null argument by the caller.
void mkcurl_response_get_body_binary_v3(const mkcurl_response_t *res,
                                        const uint8_t **p, size_t *n);

/// mkcurl_response_get_bytes_sent_v2 returns the bytes sent. Should be a
/// positive number with the fractional part equal to zero. This function calls
/// abort if passed a null argument by the caller.
double mkcurl_response_get_bytes_sent_v2(const mkcurl_response_t *res);

/// mkcurl_response_get_bytes_recv_v2 returns the bytes received. Should be a
/// positive number with the fractional part equal to zero. This function calls
/// abort if passed a null argument by the caller.
double mkcurl_response_get_bytes_recv_v2(const mkcurl_response_t *res);

/// mkcurl_response_get_logs_binary_v3 returns the logs a binary vector. It
/// calls abort if passed a null argument by the caller. We use a binary
/// vector because in principle logs MAY contain non UTF-8 data.
void mkcurl_response_get_logs_binary_v3(const mkcurl_response_t *res,
                                        const uint8_t **p, size_t *n);

/// mkcurl_response_get_request_headers_v2 returns the request line and all the
/// headers that were subsequently sent as part of the request. This function
/// never returns a null pointer. It calls abort if @p res is null.
const char *mkcurl_response_get_request_headers_v2(
    const mkcurl_response_t *res);

/// mkcurl_response_get_response_headers_binary_v3 returns the response line
/// and the headers as a binary vector. It calls abort if any of its
/// arguments is a null pointer. We use a binary vector because in principle
/// the headers MAY contain non UTF-8 data.
void mkcurl_response_get_response_headers_binary_v3(
    const mkcurl_response_t *res, const uint8_t **p, size_t *n);

/// mkcurl_response_get_certificate_chain_v2 returns the certificate chain as a
/// sequence of certificates in PEM format separated by empty lines. It will
/// call abort if @p res is a null pointer.
const char *mkcurl_response_get_certificate_chain_v2(
    const mkcurl_response_t *res);

/// mkcurl_response_get_content_type_v2 returns the contenty type (if available)
/// or an empty string. Calls abort if @p res is a null pointer.
const char *mkcurl_response_get_content_type_v2(const mkcurl_response_t *res);

/// mkcurl_response_get_http_version returns the HTTP version being used as a
/// string. The returned string will be a static string, so you don't have
/// to worry about owning it. If the version is not known, an empty string is
/// returned. This function will call abort if passed a null pointer @p res.
const char *mkcurl_response_get_http_version(const mkcurl_response_t *res);

/// mkcurl_response_delete deletes @p res. Note that @p res MAY be null.
void mkcurl_response_delete(mkcurl_response_t *res);

#ifdef __cplusplus
}  // extern "C"

#include <algorithm>
#include <memory>
#include <string>

/// mkcurl_request_deleter is a custom deleter for mkcurl_request_t.
struct mkcurl_request_deleter {
  void operator()(mkcurl_request_t *req) {
    mkcurl_request_delete(req);
  }
};

/// mkcurl_request_uptr is a unique pointer for mkcurl_request_t.
using mkcurl_request_uptr = std::unique_ptr<mkcurl_request_t,
                                            mkcurl_request_deleter>;

/// mkcurl_response_deleter is a custom deleter for mkcurl_response_t.
struct mkcurl_response_deleter {
  void operator()(mkcurl_response_t *req) {
    mkcurl_response_delete(req);
  }
};

/// mkcurl_response_uptr is a unique pointer for mkcurl_response_t.
using mkcurl_response_uptr = std::unique_ptr<mkcurl_response_t,
                                             mkcurl_response_deleter>;

/// mkcurl_request_movein_body_v2 moves @p b inside @p req
/// to be the request body. This function aborts if passed null arguments.
void mkcurl_request_movein_body_v2(mkcurl_request_uptr &req, std::string &&b);

/// mkcurl_response_moveout_body_v2 moves the response body out
/// of @p res. This function calls abort if passed a null pointer. Note
/// that the body MAY be a binary string.
std::string mkcurl_response_moveout_body_v2(mkcurl_response_uptr &res);

/// mkcurl_response_moveout_logs_v2 moves the logs out of @p res. This
/// function calls abort if @p res is null. Note that logs MAY be binary.
std::string mkcurl_response_moveout_logs_v2(mkcurl_response_uptr &res);

/// mkcurl_response_moveout_response_headers_v2 moves response headers out
/// of @p res. This function calls abort if @p res is null. Note
/// that in principle headers MAY be contain non UTF-8 data.
std::string mkcurl_response_moveout_response_headers_v2(
    mkcurl_response_uptr &res);

// If you just want to know about the API, you can stop reading here. What
// follows is the inline implementation of the library. By default it is not
// included when you include the header, but you can change this.
#ifdef MKCURL_INLINE_IMPL

#include <assert.h>

#include <chrono>
#include <sstream>
#include <string>
#include <vector>

#include <curl/curl.h>

// mkcurl_method enumerates all request methods we know.
enum class mkcurl_method {
  GET,
  POST,
  PUT
};

// Design note
// -----------
//
// We set parameters in a separate request object. Then we initialise the
// handle when we're about to perform a request. Starting from CURL v7.17.0
// CURL will copy the string you pass it, but currently it doesn't copy
// lists you pass it, and does not copy post data (both of these actually
// makes sense). So, the code in here will just initialise all the CURL
// related stuff in a single scope and our separate data structures to hold
// a request and a response, which helps to separate concerns.
//
// A flaw of this approach is that currently it doesn't allow for reusing
// the same connection. It's unclear whether that's a feature we want to
// have inside OONI. Maybe we want that for DASH. Maybe we want to implement
// DASH in golang. So, until we know, let's just keep the handle lifecycle
// confined inside the function that actually performs the request.
//
// If in the future we want to reuse a handle, we can move it to have the
// same scope of the request object. At that point we can probably also
// revisit the decision of storing configuration in the request and then
// using the request to populate the handle. Still, the fact that all
// the configuration methods of a request currently cannot fail unless
// we're out of memory is a feature that I would like to retain.

// mkcurl_request is an HTTP request.
struct mkcurl_request {
  // ca_path is the path to the CA bundle to use.
  std::string ca_path;
  // enable_http2 indicates whether we should enable HTTP2.
  bool enable_http2 = false;
  // method is the method we want to use.
  mkcurl_method method = mkcurl_method::GET;
  // url is the URL we want to use.
  std::string url;
  // headers contains the request headers.
  std::vector<std::string> headers;
  // body contains the request body (possibly a binary body).
  std::string body;
  // timeout is the time after which the request is aborted (in seconds)
  long timeout = 30;
  // proxy_url is the optional URL of the proxy to use.
  std::string proxy_url;
  // enable_fastopen will enable TCP fastopen (if possible).
  bool enable_fastopen = false;
  // follow_redir indicates whether we should follow redirects.
  bool follow_redir = false;
  // connect_to is the string to pass to CURLOPT_CONNECT_TO.
  std::string connect_to;
};

mkcurl_request_t *mkcurl_request_new_nonnull() {
  return new mkcurl_request_t{};
}

#ifndef MKCURL_ABORT
// MKCURL_ABORT allows to mock abort
#define MKCURL_ABORT abort
#endif

void mkcurl_request_set_ca_bundle_path_v2(mkcurl_request_t *req, const char *p) {
  if (req == nullptr || p == nullptr) {
    MKCURL_ABORT();
  }
  req->ca_path = p;
}

void mkcurl_request_enable_http2_v2(mkcurl_request_t *req) {
  if (req == nullptr) {
    MKCURL_ABORT();
  }
  req->enable_http2 = true;
}

void mkcurl_request_set_method_post_v2(mkcurl_request_t *req) {
  if (req == nullptr) {
    MKCURL_ABORT();
  }
  req->method = mkcurl_method::POST;
}

void mkcurl_request_set_method_put_v2(mkcurl_request_t *req) {
  if (req == nullptr) {
    MKCURL_ABORT();
  }
  req->method = mkcurl_method::PUT;
}

void mkcurl_request_set_url_v2(mkcurl_request_t *req, const char *u) {
  if (req == nullptr || u == nullptr) {
    MKCURL_ABORT();
  }
  req->url = u;
}

void mkcurl_request_add_header_v2(mkcurl_request_t *req, const char *h) {
  if (req == nullptr || h == nullptr) {
    MKCURL_ABORT();
  }
  req->headers.push_back(h);
}

void mkcurl_request_set_body_binary_v3(mkcurl_request_t *req,
                                       const uint8_t *b, size_t n) {
  if (req == nullptr || b == nullptr) {
    MKCURL_ABORT();
  }
  req->body = std::string{(const char *)b, n};
}

void mkcurl_request_set_timeout_v2(mkcurl_request_t *req, int64_t timeout) {
  if (req == nullptr) {
    MKCURL_ABORT();
  }
  req->timeout = (long)((timeout < 0L)
                            ? 0L  // which, for CURL means infinite
                            : (timeout < LONG_MAX)
                                  ? (long)timeout  // it's in range
                                  : LONG_MAX);     // curl uses a long argument
}

void mkcurl_request_set_proxy_url_v2(mkcurl_request_t *req, const char *u) {
  if (req == nullptr || u == nullptr) {
    MKCURL_ABORT();
  }
  req->proxy_url = u;
}

void mkcurl_request_enable_tcp_fastopen(mkcurl_request_t *req) {
  if (req == nullptr) {
    MKCURL_ABORT();
  }
  req->enable_fastopen = true;
}

void mkcurl_request_set_connect_to(mkcurl_request_t *req, const char *ip) {
  if (req == nullptr || ip == nullptr) {
    MKCURL_ABORT();
  }
  req->connect_to = (std::stringstream{} << "::" << ip << ":").str();
}

void mkcurl_request_enable_follow_redirect_v2(mkcurl_request_t *req) {
  if (req == nullptr) {
    MKCURL_ABORT();
  }
  req->follow_redir = true;
}

void mkcurl_request_delete(mkcurl_request_t *req) { delete req; }

// mkcurl_response is an HTTP response.
struct mkcurl_response {
  // error is the CURL error that occurred. In CURL this is an enum hence it
  // is castable to int. Therefore using int64_t should always be okay.
  int64_t error = CURLE_OK;
  // redirect_url is the URL to which we were redirected, if any.
  std::string redirect_url;
  // status_code is the HTTP status code. In CURL this is a long hence
  // using int64_t should always be wide enough.
  int64_t status_code = 0;
  // body is the response body.
  std::string body;
  // bytes_sent are the bytes sent when sending the request.
  double bytes_sent = 0.0;
  // bytes_recv are the bytes recv when receiving the response.
  double bytes_recv = 0.0;
  // logs contains the (possibly non UTF-8) logs.
  std::string logs;
  // request_headers contains the request line and the headers.
  std::string request_headers;
  // response_headers contains the response line and the headers.
  std::string response_headers;
  // certs contains a sequence of newline separated PEM certificates.
  std::string certs;
  // content_type is the response content type.
  std::string content_type;
  // http_version is the HTTP version as a static string.
  const char *http_version = "";
};

// mkcurl_log appends @p line to @p logs. It adds information on the current
// time in millisecond. It also appends a newline to the end of the line.
static void mkcurl_log(std::string &logs, std::string &&line) {
  std::stringstream ss;
  auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now().time_since_epoch());
  ss << "[" << now.count() << "] " << line << "\n";
  logs += ss.str();
}

int64_t mkcurl_response_get_error_v2(const mkcurl_response_t *res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return res->error;
}

const char *mkcurl_response_get_redirect_url_v2(const mkcurl_response_t *res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return res->redirect_url.c_str();
}

int64_t mkcurl_response_get_status_code_v2(const mkcurl_response_t *res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return res->status_code;
}

void mkcurl_response_get_body_binary_v3(const mkcurl_response_t *res,
                                        const uint8_t **p, size_t *n) {
  if (res == nullptr || p == nullptr || n == nullptr) {
    MKCURL_ABORT();
  }
  *p = (const uint8_t *)res->body.c_str();
  *n = res->body.size();
}

double mkcurl_response_get_bytes_sent_v2(const mkcurl_response_t *res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return res->bytes_sent;
}

double mkcurl_response_get_bytes_recv_v2(const mkcurl_response_t *res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return res->bytes_recv;
}

void mkcurl_response_get_logs_binary_v3(const mkcurl_response_t *res,
                                        const uint8_t **p, size_t *n) {
  if (res == nullptr || p == nullptr || n == nullptr) {
    MKCURL_ABORT();
  }
  *p = (const uint8_t *)res->logs.c_str();
  *n = res->logs.size();
}

const char *mkcurl_response_get_request_headers_v2(
    const mkcurl_response_t *res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return res->request_headers.c_str();
}

void mkcurl_response_get_response_headers_binary_v3(
    const mkcurl_response_t *res, const uint8_t **p, size_t *n) {
  if (res == nullptr || p == nullptr || n == nullptr) {
    MKCURL_ABORT();
  }
  *p = (const uint8_t *)res->response_headers.c_str();
  *n = res->response_headers.size();
}

const char *mkcurl_response_get_certificate_chain_v2(
    const mkcurl_response_t *res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return res->certs.c_str();
}

const char *mkcurl_response_get_content_type_v2(const mkcurl_response_t *res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return res->content_type.c_str();
}

const char *mkcurl_response_get_http_version(const mkcurl_response_t *res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return res->http_version;
}

void mkcurl_response_delete(mkcurl_response_t *res) { delete res; }

// mkcurl_deleter is a custom deleter for a CURL handle.
struct mkcurl_deleter {
  void operator()(CURL *handle) { curl_easy_cleanup(handle); }
};

// mkcurl_uptr is a unique pointer to a CURL handle.
using mkcurl_uptr = std::unique_ptr<CURL, mkcurl_deleter>;

// mkcurl_slist is a curl_slist with RAII semantic.
struct mkcurl_slist {
  // mkcurl_slist is the default constructor.
  mkcurl_slist() = default;
  // mkcurl_slist is the deleted copy constructor.
  mkcurl_slist(const mkcurl_slist &) = delete;
  // operator= is the deleted copy assignment.
  mkcurl_slist &operator=(const mkcurl_slist &) = delete;
  // mkcurl_slist is the deleted move constructor.
  mkcurl_slist(mkcurl_slist &&) = delete;
  // operator= is the deleted move assignment.
  mkcurl_slist &operator=(mkcurl_slist &&) = delete;
  // ~mkcurl_slist is the destructor.
  ~mkcurl_slist() { curl_slist_free_all(p); }
  // p is the pointer to the wrapped slist.
  curl_slist *p = nullptr;
};

#ifndef MKCURL_EASY_INIT
// MKCURL_EASY_INIT allows to mock curl_easy_init
#define MKCURL_EASY_INIT curl_easy_init
#endif

#ifndef MKCURL_SLIST_APPEND
// MKCURL_SLIST_APPEND allows to mock curl_slist_append
#define MKCURL_SLIST_APPEND curl_slist_append
#endif

#ifndef MKCURL_EASY_SETOPT
// MKCURL_EASY_SETOPT allows to mock curl_easy_setopt
#define MKCURL_EASY_SETOPT curl_easy_setopt
#endif

#ifndef MKCURL_EASY_PERFORM
// MKCURL_EASY_PERFORM allows to mock curl_easy_perform
#define MKCURL_EASY_PERFORM curl_easy_perform
#endif

#ifndef MKCURL_EASY_GETINFO
// MKCURL_EASY_GETINFO allows to mock curl_easy_getinfo
#define MKCURL_EASY_GETINFO curl_easy_getinfo
#endif

extern "C" {

static size_t mkcurl_body_cb(
    char *ptr, size_t size, size_t nmemb, void *userdata) noexcept {
  if (nmemb <= 0) {
    return 0;  // This means "no body"
  }
  if (size > SIZE_MAX / nmemb) {
    // If size is zero we end up into this branch.
    return 0;
  }
  if (ptr == nullptr || userdata == nullptr) {
    MKCURL_ABORT();
  }
  auto realsiz = size * nmemb;  // Overflow or zero not possible (see above)
  auto res = static_cast<mkcurl_response_t *>(userdata);
  res->body += std::string{ptr, realsiz};
  // From fwrite(3): "[the return value] equals the number of bytes
  // written _only_ when `size` equals `1`". See also
  // https://sourceware.org/git/?p=glibc.git;a=blob;f=libio/iofwrite.c;h=800341b7da546e5b7fd2005c5536f4c90037f50d;hb=HEAD#l29
  return nmemb;
}

static int mkcurl_debug_cb(CURL *handle,
                           curl_infotype type,
                           char *data,
                           size_t size,
                           void *userptr) {
  (void)handle;
  if (data == nullptr || userptr == nullptr) {
    MKCURL_ABORT();
  }
  auto res = static_cast<mkcurl_response_t *>(userptr);

  auto log_many_lines = [&](std::string prefix, const std::string &str) {
    std::stringstream ss;
    ss << str;
    std::string line;
    while (std::getline(ss, line, '\n')) {
      std::stringstream logline;
      if (!prefix.empty()) {
        logline << prefix << " ";
      }
      logline << line;
      mkcurl_log(res->logs, logline.str());
    }
  };

  switch (type) {
    case CURLINFO_TEXT:
      log_many_lines("", std::string{(const char *)data, size});
      break;
    case CURLINFO_HEADER_IN:
      {
        std::string s{(const char *)data, size};
        log_many_lines("<", s);
        res->response_headers += s;
      }
      break;
    case CURLINFO_DATA_IN:
      log_many_lines("<data:", std::to_string(size));
      break;
    case CURLINFO_SSL_DATA_IN:
      log_many_lines("<tls_data:", std::to_string(size));
      break;
    case CURLINFO_HEADER_OUT:
      {
        std::string s{(const char *)data, size};
        log_many_lines(">", s);
        res->request_headers += s;
      }
      break;
    case CURLINFO_DATA_OUT:
      log_many_lines(">data:", std::to_string(size));
      break;
    case CURLINFO_SSL_DATA_OUT:
      log_many_lines(">tls_data:", std::to_string(size));
      break;
    case CURLINFO_END:
      /* NOTHING */
      break;
  }

  // Note regarding counting TLS data
  // ````````````````````````````````
  //
  // I am using the technique recommended by Stenberg on Stack Overflow [1]. It
  // was initially not clear to me whether cURL using OpenSSL counted the data
  // twice, once encrypted and once in clear text. However, using cURL using
  // OpenSSL on Linux and reading the source code [2] helped me to clarify that
  // it does indeed the right thing [3]. When using other TLS backends, it may
  // be that TLS data is not counted, but that's okay since we tell to users
  // that this is an estimate of the amount of used data.
  //
  // Notes
  // `````
  //
  // .. [1] https://stackoverflow.com/a/26905099
  //
  // .. [2] https://github.com/curl/curl/blob/6684653b/lib/vtls/openssl.c#L2295
  //
  // .. [3] the SSL function used is SSL_CTX_set_msg_callback which "[is] never
  //        [called for] application_data(23) because the callback will only be
  //        called for protocol messages" [4].
  //
  // .. [4] https://www.openssl.org/docs/man1.1.0/ssl/SSL_CTX_set_msg_callback.html
  switch (type) {
    case CURLINFO_HEADER_IN:
    case CURLINFO_DATA_IN:
    case CURLINFO_SSL_DATA_IN:
      res->bytes_recv += (double)size;
      break;
    case CURLINFO_HEADER_OUT:
    case CURLINFO_DATA_OUT:
    case CURLINFO_SSL_DATA_OUT:
      res->bytes_sent += (double)size;
      break;
    case CURLINFO_TEXT:
    case CURLINFO_END:
      /* NOTHING */
      break;
  }

  return 0;
}

}  // extern "C"

// TODO(bassosimone):
//
// 1. Allow to disable CURLOPT_SSL_VERIFYPEER
//
// 2. Allow to disable CURLOPT_SSL_VERIFYHOST
//
// 3. Allow to set a specific SSL version with CURLOPT_SSLVERSION
mkcurl_response_t *mkcurl_request_perform_nonnull(const mkcurl_request_t *req) {
  if (req == nullptr) {
    MKCURL_ABORT();
  }
  mkcurl_response_uptr res{new mkcurl_response_t{}};  // new doesn't fail
  mkcurl_uptr handle{MKCURL_EASY_INIT()};
  if (!handle) {
    res->error = CURLE_OUT_OF_MEMORY;
    mkcurl_log(res->logs, "curl_easy_init() failed");
    return res.release();
  }
  mkcurl_slist headers;  // This must have function scope
  for (auto &s : req->headers) {
    if ((headers.p = MKCURL_SLIST_APPEND(headers.p, s.c_str())) == nullptr) {
      res->error = CURLE_OUT_OF_MEMORY;
      mkcurl_log(res->logs, "curl_slist_append() failed");
      return res.release();
    }
  }
  mkcurl_slist connect_to_settings; // This must have function scope
  if (!req->connect_to.empty()) {
    connect_to_settings.p = MKCURL_SLIST_APPEND(
        connect_to_settings.p, req->connect_to.c_str());
    if (connect_to_settings.p == nullptr) {
      res->error = CURLE_OUT_OF_MEMORY;
      mkcurl_log(res->logs, "curl_slist_append() failed");
      return res.release();
    }
    res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_CONNECT_TO,
                                    connect_to_settings.p);
    if (res->error != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_CONNECT_TO) failed");
      return res.release();
    }
  }
  if (req->enable_fastopen &&
      (res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_TCP_FASTOPEN,
                                       1L)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_TCP_FASTOPEN) failed");
    return res.release();
  }
  if (!req->ca_path.empty() &&
      (res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_CAINFO,
                                       req->ca_path.c_str())) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_CAINFO) failed");
    return res.release();
  }
  if (req->enable_http2 == true &&
      (res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_HTTP_VERSION,
                                       CURL_HTTP_VERSION_2_0)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_HTTP_VERSION) failed");
    return res.release();
  }
  if (req->method == mkcurl_method::POST ||
      req->method == mkcurl_method::PUT) {
    // Disable sending `Expect: 100 continue`. There are actually good
    // arguments against NOT sending this specific HTTP header by default
    // with P{OS,U}T <https://curl.haxx.se/mail/lib-2017-07/0013.html>.
    if ((headers.p = MKCURL_SLIST_APPEND(headers.p, "Expect:")) == nullptr) {
      res->error = CURLE_OUT_OF_MEMORY;
      mkcurl_log(res->logs, "curl_slist_append() failed");
      return res.release();
    }
    if ((res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_POST,
                                         1L)) != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_POST) failed");
      return res.release();
    }
    if ((res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_POSTFIELDS,
                                         req->body.c_str())) != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_POSTFIELDS) failed");
      return res.release();
    }
    // The following is very important to allow us to upload any kind of
    // binary file, otherwise CURL will use strlen(). We do not need to
    // send more than 2 GiB of data, hence we can safely limit ourself to
    // using CURLOPT_POSTFIELDSIZE that takes a `long` argument.
    if (req->body.size() > LONG_MAX) {
      mkcurl_log(res->logs, "Body larger than LONG_MAX");
      return res.release();
    }
    if ((res->error = MKCURL_EASY_SETOPT(
             handle.get(), CURLOPT_POSTFIELDSIZE,
             (long)req->body.size())) != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_setopt(MKCURLOPT_POSTFIELDSIZE) failed");
      return res.release();
    }
    if (req->method == mkcurl_method::PUT &&
        (res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_CUSTOMREQUEST,
                                         "PUT")) != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_CUSTOMREQUEST) failed");
      return res.release();
    }
  }
  if (headers.p != nullptr &&
      (res->error = MKCURL_EASY_SETOPT(
           handle.get(), CURLOPT_HTTPHEADER, headers.p)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_HTTPHEADER) failed");
    return res.release();
  }
  if ((res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_URL,
                                       req->url.c_str())) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_URL) failed");
    return res.release();
  }
  if ((res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_WRITEFUNCTION,
                                       mkcurl_body_cb)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_WRITEFUNCTION) failed");
    return res.release();
  }
  if ((res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_WRITEDATA,
                                       res.get())) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_WRITEDATA) failed");
    return res.release();
  }
  // CURL uses MSG_NOSIGNAL where available (i.e. Linux) and SO_NOSIGPIPE
  // where available (i.e. BSD). This covers all the UNIX operating systems
  // that we care about (Android, Linux, iOS, macOS). We additionally need
  // to avoid signals because we are acting as a library that is integrated
  // into several different languages, so stealing the signal handler from
  // the language MAY have a negative impact.
  //
  // Note: disabling signal handlers makes the default non-threaded CURL
  // resolver non interruptible, so we need to make sure we recompile using
  // either the threaded or the c-ares CURL backend. TODO(bassosimone)
  if ((res->error = MKCURL_EASY_SETOPT(
           handle.get(), CURLOPT_NOSIGNAL, 1L)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_NOSIGNAL) failed");
    return res.release();
  }
  if (req->timeout >= 0 &&
      (res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_TIMEOUT,
                                       req->timeout)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_TIMEOUT) failed");
    return res.release();
  }
  if ((res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_DEBUGFUNCTION,
                                       mkcurl_debug_cb)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_DEBUGFUNCTION) failed");
    return res.release();
  }
  if ((res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_DEBUGDATA,
                                       res.get())) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_DEBUGDATA) failed");
    return res.release();
  }
  if ((res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_VERBOSE,
                                       1L)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_VERBOSE) failed");
    return res.release();
  }
  if (!req->proxy_url.empty() &&
      (res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_PROXY,
                                       req->proxy_url.c_str())) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_PROXY) failed");
    return res.release();
  }
  if (req->follow_redir == true &&
      (res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_FOLLOWLOCATION,
                                       1L)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_FOLLOWLOCATION) failed");
    return res.release();
  }
  if ((res->error = MKCURL_EASY_SETOPT(handle.get(), CURLOPT_CERTINFO,
                                       1L)) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_setopt(CURLOPT_CERTINFO) failed");
    return res.release();
  }
  if ((res->error = MKCURL_EASY_PERFORM(handle.get())) != CURLE_OK) {
    mkcurl_log(res->logs, "curl_easy_perform() failed");
    return res.release();
  }
  {
    long status_code = 0;
    if ((res->error = MKCURL_EASY_GETINFO(
             handle.get(), CURLINFO_RESPONSE_CODE, &status_code)) != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_getinfo(CURLINFO_RESPONSE_CODE) failed");
      return res.release();
    }
    res->status_code = (int64_t)status_code;
  }
  {
    char *url = nullptr;
    if ((res->error = MKCURL_EASY_GETINFO(
             handle.get(), CURLINFO_REDIRECT_URL, &url)) != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_getinfo(CURLINFO_REDIRECT_URL) failed");
      return res.release();
    }
    if (url != nullptr) res->redirect_url = url;
  }
  {
    curl_certinfo *certinfo = nullptr;
    if ((res->error = MKCURL_EASY_GETINFO(
             handle.get(), CURLINFO_CERTINFO, &certinfo)) != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_getinfo(CURLINFO_CERTINFO) failed");
      return res.release();
    }
    if (certinfo != nullptr && certinfo->num_of_certs > 0) {
      for (int i = 0; i < certinfo->num_of_certs; i++) {
        for (auto slist = certinfo->certinfo[i]; slist; slist = slist->next) {
          if (slist->data != nullptr) {
            // Just pass in the certificates and ignore the rest.
            std::string s = slist->data;
            if (s.find("Cert:") == 0) {
              res->certs += s.substr(5);
              res->certs += "\n";
            }
          }
        }
      }
    }
  }
  {
    char *ct = nullptr;
    if ((res->error = MKCURL_EASY_GETINFO(
             handle.get(), CURLINFO_CONTENT_TYPE, &ct)) != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_getinfo(CURLINFO_CONTENT_TYPE) failed");
      return res.release();
    }
    if (ct != nullptr) res->content_type = ct;
  }
  {
    long httpv = 0L;
    if ((res->error = MKCURL_EASY_GETINFO(
            handle.get(), CURLINFO_HTTP_VERSION, &httpv)) != CURLE_OK) {
      mkcurl_log(res->logs, "curl_easy_getinfo(CURLINFO_HTTP_VERSION) failed");
      return res.release();
    }
    switch (httpv) {
      case CURL_HTTP_VERSION_1_0:
        res->http_version = "HTTP/1.0";
        break;
      case CURL_HTTP_VERSION_1_1:
        res->http_version = "HTTP/1.1";
        break;
      case CURL_HTTP_VERSION_2_0:
        res->http_version = "HTTP/2";
        break;
      default:
        res->http_version = "";
        break;
    }
  }
  mkcurl_log(res->logs, "curl_easy_perform() success");
  return res.release();
}

void mkcurl_request_movein_body_v2(mkcurl_request_uptr &req, std::string &&b) {
  if (req == nullptr) {
    MKCURL_ABORT();
  }
  std::swap(req->body, b);
}

std::string mkcurl_response_moveout_body_v2(mkcurl_response_uptr &res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return std::move(res->body);
}

std::string mkcurl_response_moveout_logs_v2(mkcurl_response_uptr &res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return std::move(res->logs);
}

std::string mkcurl_response_moveout_response_headers_v2(
    mkcurl_response_uptr &res) {
  if (res == nullptr) {
    MKCURL_ABORT();
  }
  return std::move(res->response_headers);
}

#endif  // MKCURL_INLINE_IMPL
#endif  // __cplusplus
#endif  // MEASUREMENT_KIT_MKCURL_H
