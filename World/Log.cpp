#include "Log.h"

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <chrono>

#include <boost/shared_ptr.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/syslog_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/detail/process_id.hpp>
#include <boost/log/attributes/current_process_name.hpp>
#include <boost/log/detail/thread_id.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/expressions/formatters/stream.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/format.hpp>


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace bl = boost::log;
namespace bl_attrs = boost::log::attributes;
namespace bl_src = boost::log::sources;
namespace bl_sinks = boost::log::sinks;
namespace bl_expr = boost::log::expressions;
namespace bl_keywords = boost::log::keywords;

using boost::shared_ptr;

using namespace std;

// http://sourceforge.net/p/boost-log/discussion/710021/thread/e90226f5/
//[ example_tutorial_trivial_with_filtering
void LogInit(bool consoleLogEnabled, bool fileLogEnabled)
{
  bl::core::get()->add_global_attribute("Process", bl_attrs::current_process_name());
  bl::core::get()->add_global_attribute("Scope", bl_attrs::named_scope());

  if (consoleLogEnabled) {
    bl::add_console_log(
      std::cout,
      keywords::format = (
        bl_expr::stream
        << "["
        << bl_expr::attr<boost::log::attributes::current_process_name::value_type>("Process")
        //						<< ":"
        //						<< bl_expr::attr<boost::log::attributes::current_process_id::value_type>("ProcessID")
        //						<< ":"
        //						<< bl_expr::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID")
        << "] ["
        << bl_expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
        << "]["
        << bl::trivial::severity
        << "]: "
        //						"[" << bl_expr::format_named_scope("Scope",
        //														   bl_keywords::format = "%n",
        //														   bl_keywords::iteration = bl_expr::forward)
        //						        << "]: "
        << bl_expr::message
        )
      );
  }

  if (fileLogEnabled) {
    logging::add_file_log
      (
        keywords::file_name = "Log_%N.log",                                           /*< file name pattern >*/
        keywords::rotation_size = 50 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), /*< ...or at midnight >*/
        keywords::format = (
          bl_expr::stream
          << "["
          << bl_expr::attr<boost::log::attributes::current_process_name::value_type>("Process")
          //					<< ":"
          //					<< bl_expr::attr<boost::log::attributes::current_process_id::value_type>("ProcessID")
          //					<< ":"
          //					<< bl_expr::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID")
          << "] ["
          << bl_expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
          << "]["
          << bl::trivial::severity
          << "]: "
          << bl_expr::message
          )                                 /*< log record format >*/
        );
  }

  logging::core::get()->set_filter
    (
      logging::trivial::severity >= logging::trivial::trace
      );
}