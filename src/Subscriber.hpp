/*
 * Copyright (C) 2018 Open Source Robotics Foundation
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
 *
*/

#ifndef SOSS__DDS__INTERNAL__SUBSCRIBER_HPP
#define SOSS__DDS__INTERNAL__SUBSCRIBER_HPP

#include "DDSMiddlewareException.hpp"
#include "Participant.hpp"

#include <soss/SystemHandle.hpp>

#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/types/DynamicDataPtr.h>

namespace soss {
namespace dds {


class Participant;

class Subscriber : private fastrtps::SubscriberListener
{
public:
    Subscriber(
            Participant* participant,
            const std::string& topic_name,
            const std::string& message_type,
            TopicSubscriberSystem::SubscriptionCallback soss_callback);

    virtual ~Subscriber();

    Subscriber(const Subscriber& rhs) = delete;
    Subscriber& operator = (const Subscriber& rhs) = delete;
    Subscriber(Subscriber&& rhs) = delete;
    Subscriber& operator = (Subscriber&& rhs) = delete;

    void receive(const std::string& message); //dynamic type

private:
    void onSubscriptionMatched(
            fastrtps::Subscriber* sub,
            fastrtps::rtps::MatchingInfo& info) override;

    void onNewDataMessage(
            fastrtps::Subscriber* sub) override;

    fastrtps::Subscriber* dds_subscriber_;
    fastrtps::types::DynamicData_ptr dynamic_data_;

    const std::string topic_name_;
    const std::string message_type_;

    TopicSubscriberSystem::SubscriptionCallback soss_callback_;
};


} // namespace dds
} // namespace soss

#endif // SOSS__DDS__INTERNAL__SUBSCRIBER_HPP
