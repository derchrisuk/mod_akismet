/*
 * mod_akismet.c - Apache module that enables you to detect spam comments
 * before your application handler by Akismet anti-comment-spam service
 *
 * Copyright (C) 2009 Yoichi Kawasaki All rights reserved.
 * yk55.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _AKISMET_H_
#define _AKISMET_H_

#include "httpd.h"

/* Akismet API's base domain to be used by mod_akismet */
#define AKISMET_API_SERVER                 "rest.akismet.com"
/* Akismet API's version to be used by mod_akismet */
#define AKISMET_API_VERSION                "1.1"
/* Akismet API's Port number */
#define AKISMET_API_PORT                   "80"
/* Akismet API's key verification method name */
#define AKISMET_API_METHOD_VERIFY_KEY      "verify-key"
/* Akismet API's spam comment check method name */
#define AKISMET_API_METHOD_COMMENT_CHECK   "comment-check"
/* The response string that Key-verification method returns if the key is valid */
#define AKISMET_API_RES_VERIFY_KEY_OK      "valid"
/* The response string that comment-check method returns if the comment is spam */
#define AKISMET_API_RES_COMMENT_IS_SPAM    "true"
/* HTTP request timeout in milsec */
#define AKISMET_API_REQ_TIMEOUT            (100)
/* UserAgent name to be used by mod_akismet in requesting to Akismet API */
#define AKISMET_API_REQ_USERAGENT          "mod_akismet/1.0"

typedef enum {
    AKISMET_OK   = 0,
    AKISMET_SPAM,
    AKISMET_KEY_INVALID,
    AKISMET_BAD_PARAM_ERROR,
    AKISMET_HTTP_POST_ERROR
}AkismetCode;

typedef struct {
    char *apikey;
    char *blogurl;
    char *ip;
    char *ua;
    char *ref;
    char *comment;
    char *comment_author;
    char *comment_author_email;
    char *comment_author_url;
    char *comment_permalink;
} akismet_comment_check_request;

AkismetCode
 akismet_verify_key(request_rec *r, const char *apikey, const char* blggurl);

AkismetCode
 akismet_comment_check(request_rec *r, akismet_comment_check_request *acc_req );


#endif
