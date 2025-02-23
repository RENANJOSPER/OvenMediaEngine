//==============================================================================
//
//  OvenMediaEngine
//
//  Created by Hyunjun Jang
//  Copyright (c) 2020 AirenSoft. All rights reserved.
//
//==============================================================================
#include "application.h"
#include "common.h"
namespace serdes
{
	Json::Value JsonFromMetrics(const std::shared_ptr<const mon::CommonMetrics> &metrics)
	{
		if (metrics == nullptr)
		{
			return Json::nullValue;
		}

		Json::Value value;

		SetTimestamp(value, "createdTime", metrics->GetCreatedTime());
		SetTimestamp(value, "lastUpdatedTime", metrics->GetLastUpdatedTime());
		SetInt64(value, "totalBytesIn", metrics->GetTotalBytesIn());
		SetInt64(value, "totalBytesOut", metrics->GetTotalBytesOut());
		SetInt64(value, "avgThroughputIn", metrics->GetAvgThroughputIn());
		SetInt64(value, "avgThroughputOut", metrics->GetAvgThroughputOut());		
		SetInt64(value, "maxThroughputIn", metrics->GetMaxThroughputIn());
		SetInt64(value, "maxThroughputOut", metrics->GetMaxThroughputOut());
		SetTimestamp(value, "lastRecvTime", metrics->GetLastRecvTime());
		SetTimestamp(value, "lastSentTime", metrics->GetLastSentTime());
		SetInt(value, "totalConnections", metrics->GetTotalConnections());
		SetInt(value, "maxTotalConnections", metrics->GetMaxTotalConnections());
		SetTimestamp(value, "maxTotalConnectionTime", metrics->GetMaxTotalConnectionsTime());

		Json::Value &connections = value["connections"];
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::Webrtc).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::Webrtc));
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::LLDash).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::LLDash));
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::Hls).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::Hls));
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::LLHls).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::LLHls));
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::Dash).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::Dash));
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::Ovt).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::Ovt));
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::File).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::File));
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::RtmpPush).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::RtmpPush));
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::MpegtsPush).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::MpegtsPush));
		SetInt(connections, ov::String::FormatString("%s", StringFromPublisherType(PublisherType::Thumbnail).LowerCaseString().CStr()).CStr(), metrics->GetConnections(PublisherType::Thumbnail));

		return value;
	}

	Json::Value JsonFromStreamMetrics(const std::shared_ptr<const mon::StreamMetrics> &metrics)
	{
		Json::Value value = JsonFromMetrics(metrics);

		if (value.isNull())
		{
			return value;
		}

		SetTimeInterval(value, "requestTimeToOrigin", metrics->GetOriginConnectionTimeMSec());
		SetTimeInterval(value, "responseTimeFromOrigin", metrics->GetOriginSubscribeTimeMSec());

		return value;
	}
}  // namespace serdes