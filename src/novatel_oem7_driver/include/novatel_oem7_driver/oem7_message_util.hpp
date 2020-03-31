////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020 NovAtel Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __OEM7_MESSAGE_UTIL_HPP__
#define __OEM7_MESSAGE_UTIL_HPP__

#include "novatel_oem7_msgs/Oem7Header.h"
#include "novatel_oem7_msgs/Oem7RawMsg.h"

#include "oem7_raw_message_if.hpp"
using novatel_oem7::Oem7RawMessageIf;

#include "oem7_messages.h"

#include <ros/ros.h>

namespace novatel_oem7_driver
{

  void initializeOem7MessageUtil(ros::NodeHandle& nh);
  int getOem7MessageId(const std::string& msg_name);
  const std::string& getOem7MessageName(int msg_id);

  /**
   * Populates Oem7 Binary message header from raw message
   *
   */
  void getOem7Header(
      const Oem7RawMessageIf::ConstPtr& raw_msg, ///< [in] Raw binary message
      novatel_oem7_msgs::Oem7Header::Type& hdr   ///< [out] Oem7 Message Header
      );

  /**
   * Populates Oem7 Binary message header from 'short' raw message
   *
   */
  void getOem7ShortHeader(
      const Oem7RawMessageIf::ConstPtr& raw_msg, ///< [in] Raw binary message
      novatel_oem7_msgs::Oem7Header::Type& hdr   ///< [out] Oem7 Message Header
      );

  size_t Get_INSCONFIG_NumTranslations(const INSCONFIG_FixedMem* insconfig);

  const INSCONFIG_TranslationMem* Get_INSCONFIG_Translation(const INSCONFIG_FixedMem* insconfig, size_t idx);

  size_t Get_INSCONFIG_NumRotations(const INSCONFIG_FixedMem* insconfig);

  const INSCONFIG_RotationMem* Get_INSCONFIG_Rotation(const INSCONFIG_FixedMem* insconfig, size_t idx);


  size_t Get_PSRDOP2_NumSystems(const PSRDOP2_FixedMem* psrdop2);
  const PSRDOP2_SystemMem* Get_PSRDOP2_System(const PSRDOP2_FixedMem* psrdop2, size_t idx);
}


#endif
