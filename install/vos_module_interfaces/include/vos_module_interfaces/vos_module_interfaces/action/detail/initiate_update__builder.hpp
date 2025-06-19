// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vos_module_interfaces:action/InitiateUpdate.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__BUILDER_HPP_
#define VOS_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vos_module_interfaces/action/detail/initiate_update__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vos_module_interfaces
{

namespace action
{

namespace builder
{

class Init_InitiateUpdate_Goal_expected_hash
{
public:
  explicit Init_InitiateUpdate_Goal_expected_hash(::vos_module_interfaces::action::InitiateUpdate_Goal & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::action::InitiateUpdate_Goal expected_hash(::vos_module_interfaces::action::InitiateUpdate_Goal::_expected_hash_type arg)
  {
    msg_.expected_hash = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_Goal msg_;
};

class Init_InitiateUpdate_Goal_force
{
public:
  explicit Init_InitiateUpdate_Goal_force(::vos_module_interfaces::action::InitiateUpdate_Goal & msg)
  : msg_(msg)
  {}
  Init_InitiateUpdate_Goal_expected_hash force(::vos_module_interfaces::action::InitiateUpdate_Goal::_force_type arg)
  {
    msg_.force = std::move(arg);
    return Init_InitiateUpdate_Goal_expected_hash(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_Goal msg_;
};

class Init_InitiateUpdate_Goal_target_version
{
public:
  explicit Init_InitiateUpdate_Goal_target_version(::vos_module_interfaces::action::InitiateUpdate_Goal & msg)
  : msg_(msg)
  {}
  Init_InitiateUpdate_Goal_force target_version(::vos_module_interfaces::action::InitiateUpdate_Goal::_target_version_type arg)
  {
    msg_.target_version = std::move(arg);
    return Init_InitiateUpdate_Goal_force(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_Goal msg_;
};

class Init_InitiateUpdate_Goal_update_url
{
public:
  explicit Init_InitiateUpdate_Goal_update_url(::vos_module_interfaces::action::InitiateUpdate_Goal & msg)
  : msg_(msg)
  {}
  Init_InitiateUpdate_Goal_target_version update_url(::vos_module_interfaces::action::InitiateUpdate_Goal::_update_url_type arg)
  {
    msg_.update_url = std::move(arg);
    return Init_InitiateUpdate_Goal_target_version(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_Goal msg_;
};

class Init_InitiateUpdate_Goal_module_name
{
public:
  Init_InitiateUpdate_Goal_module_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitiateUpdate_Goal_update_url module_name(::vos_module_interfaces::action::InitiateUpdate_Goal::_module_name_type arg)
  {
    msg_.module_name = std::move(arg);
    return Init_InitiateUpdate_Goal_update_url(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::action::InitiateUpdate_Goal>()
{
  return vos_module_interfaces::action::builder::Init_InitiateUpdate_Goal_module_name();
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace action
{

namespace builder
{

class Init_InitiateUpdate_Result_report
{
public:
  explicit Init_InitiateUpdate_Result_report(::vos_module_interfaces::action::InitiateUpdate_Result & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::action::InitiateUpdate_Result report(::vos_module_interfaces::action::InitiateUpdate_Result::_report_type arg)
  {
    msg_.report = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_Result msg_;
};

class Init_InitiateUpdate_Result_success
{
public:
  Init_InitiateUpdate_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitiateUpdate_Result_report success(::vos_module_interfaces::action::InitiateUpdate_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_InitiateUpdate_Result_report(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::action::InitiateUpdate_Result>()
{
  return vos_module_interfaces::action::builder::Init_InitiateUpdate_Result_success();
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace action
{

namespace builder
{

class Init_InitiateUpdate_Feedback_progress_percentage
{
public:
  explicit Init_InitiateUpdate_Feedback_progress_percentage(::vos_module_interfaces::action::InitiateUpdate_Feedback & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::action::InitiateUpdate_Feedback progress_percentage(::vos_module_interfaces::action::InitiateUpdate_Feedback::_progress_percentage_type arg)
  {
    msg_.progress_percentage = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_Feedback msg_;
};

class Init_InitiateUpdate_Feedback_status_message
{
public:
  Init_InitiateUpdate_Feedback_status_message()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitiateUpdate_Feedback_progress_percentage status_message(::vos_module_interfaces::action::InitiateUpdate_Feedback::_status_message_type arg)
  {
    msg_.status_message = std::move(arg);
    return Init_InitiateUpdate_Feedback_progress_percentage(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::action::InitiateUpdate_Feedback>()
{
  return vos_module_interfaces::action::builder::Init_InitiateUpdate_Feedback_status_message();
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace action
{

namespace builder
{

class Init_InitiateUpdate_SendGoal_Request_goal
{
public:
  explicit Init_InitiateUpdate_SendGoal_Request_goal(::vos_module_interfaces::action::InitiateUpdate_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::action::InitiateUpdate_SendGoal_Request goal(::vos_module_interfaces::action::InitiateUpdate_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_SendGoal_Request msg_;
};

class Init_InitiateUpdate_SendGoal_Request_goal_id
{
public:
  Init_InitiateUpdate_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitiateUpdate_SendGoal_Request_goal goal_id(::vos_module_interfaces::action::InitiateUpdate_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_InitiateUpdate_SendGoal_Request_goal(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::action::InitiateUpdate_SendGoal_Request>()
{
  return vos_module_interfaces::action::builder::Init_InitiateUpdate_SendGoal_Request_goal_id();
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace action
{

namespace builder
{

class Init_InitiateUpdate_SendGoal_Response_stamp
{
public:
  explicit Init_InitiateUpdate_SendGoal_Response_stamp(::vos_module_interfaces::action::InitiateUpdate_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::action::InitiateUpdate_SendGoal_Response stamp(::vos_module_interfaces::action::InitiateUpdate_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_SendGoal_Response msg_;
};

class Init_InitiateUpdate_SendGoal_Response_accepted
{
public:
  Init_InitiateUpdate_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitiateUpdate_SendGoal_Response_stamp accepted(::vos_module_interfaces::action::InitiateUpdate_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_InitiateUpdate_SendGoal_Response_stamp(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::action::InitiateUpdate_SendGoal_Response>()
{
  return vos_module_interfaces::action::builder::Init_InitiateUpdate_SendGoal_Response_accepted();
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace action
{

namespace builder
{

class Init_InitiateUpdate_GetResult_Request_goal_id
{
public:
  Init_InitiateUpdate_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vos_module_interfaces::action::InitiateUpdate_GetResult_Request goal_id(::vos_module_interfaces::action::InitiateUpdate_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::action::InitiateUpdate_GetResult_Request>()
{
  return vos_module_interfaces::action::builder::Init_InitiateUpdate_GetResult_Request_goal_id();
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace action
{

namespace builder
{

class Init_InitiateUpdate_GetResult_Response_result
{
public:
  explicit Init_InitiateUpdate_GetResult_Response_result(::vos_module_interfaces::action::InitiateUpdate_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::action::InitiateUpdate_GetResult_Response result(::vos_module_interfaces::action::InitiateUpdate_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_GetResult_Response msg_;
};

class Init_InitiateUpdate_GetResult_Response_status
{
public:
  Init_InitiateUpdate_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitiateUpdate_GetResult_Response_result status(::vos_module_interfaces::action::InitiateUpdate_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_InitiateUpdate_GetResult_Response_result(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::action::InitiateUpdate_GetResult_Response>()
{
  return vos_module_interfaces::action::builder::Init_InitiateUpdate_GetResult_Response_status();
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace action
{

namespace builder
{

class Init_InitiateUpdate_FeedbackMessage_feedback
{
public:
  explicit Init_InitiateUpdate_FeedbackMessage_feedback(::vos_module_interfaces::action::InitiateUpdate_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::action::InitiateUpdate_FeedbackMessage feedback(::vos_module_interfaces::action::InitiateUpdate_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_FeedbackMessage msg_;
};

class Init_InitiateUpdate_FeedbackMessage_goal_id
{
public:
  Init_InitiateUpdate_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitiateUpdate_FeedbackMessage_feedback goal_id(::vos_module_interfaces::action::InitiateUpdate_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_InitiateUpdate_FeedbackMessage_feedback(msg_);
  }

private:
  ::vos_module_interfaces::action::InitiateUpdate_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::action::InitiateUpdate_FeedbackMessage>()
{
  return vos_module_interfaces::action::builder::Init_InitiateUpdate_FeedbackMessage_goal_id();
}

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__BUILDER_HPP_
