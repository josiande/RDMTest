/******************************************************************************
 * Copyright 2020 ETC Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************
 * This file is a part of RDM. For more information, go to:
 * https://github.com/ETCLabs/RDM
 *****************************************************************************/

/*
 * IMPORTANT NOTE: If you change this file, you must also change the template located at
 * tools/version/templates/version.h.in.
 */

/**
 * @file rdm/version.h
 * @brief Provides the current version of the RDM library.
 */

#ifndef RDM_VERSION_H_
#define RDM_VERSION_H_

/* clang-format off */

/** 
 * @defgroup rdm RDM
 * @brief Implementation of the RDM protocol.
 *
 * @{
 */

/**
 * @name RDM version numbers
 * @{
 */
#define RDM_VERSION_MAJOR 0 /**< The major version. */
#define RDM_VERSION_MINOR 2 /**< The minor version. */
#define RDM_VERSION_PATCH 0 /**< The patch version. */
#define RDM_VERSION_BUILD 10 /**< The build number. */
/**
 * @}
 */

/**
 * @name RDM version strings
 * @{
 */
#define RDM_VERSION_STRING "0.2.0.10"
#define RDM_VERSION_DATESTR "19.Aug.2020"
#define RDM_VERSION_COPYRIGHT "Copyright 2020 ETC Inc."
#define RDM_VERSION_PRODUCTNAME "RDM"
/**
 * @}
 */

/**
 * @defgroup rdm_c Core API
 * @ingroup rdm
 * @brief The core RDM interface, in pure C99.
 */

/**
 * @defgroup rdm_cpp C++ API
 * @ingroup rdm
 * @brief Header-only C++ wrappers for the RDM interface.
 */

/**
 * @}
 */

#endif /* RDM_VERSION_H_ */
