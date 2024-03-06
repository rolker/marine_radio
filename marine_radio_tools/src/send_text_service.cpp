#include "ros/ros.h"
#include "marine_radio_msgs/TransmitText.h"
#include "marine_radio_msgs/TransmitAudio.h"

#include "flite/flite.h"
extern "C"
{
	cst_voice* register_cmu_us_kal();
}


class TextToRadioTransmission
{
public:
  TextToRadioTransmission()
    :node_handle_("~")
  {
    transmit_audio_service_ = node_handle_.param("transmit_audio_service", transmit_audio_service_);
    flite_init();
    voice_ = register_cmu_us_kal();
    transmit_text_service_ = node_handle_.advertiseService("transmit_text", &TextToRadioTransmission::transmitTextService, this);

  }


private:
  bool transmitTextService(marine_radio_msgs::TransmitText::Request& req, marine_radio_msgs::TransmitText::Response& resp)
  {
    auto wave = flite_text_to_wave(req.message.c_str(), voice_);
    resp.transmit_duration = wave->num_samples/float(wave->sample_rate);

    marine_radio_msgs::TransmitAudio ta;
    ta.request.message.audio_data.channel_id = req.channel_id;
    ta.request.message.audio_info.channels = 1;
    ta.request.message.audio_info.sample_rate = wave->sample_rate;
    ta.request.message.audio_info.sample_format = "S16LE";
    ta.request.message.audio_info.coding_format = "WAVE";

    ta.request.message.audio_data.audio.data.resize(wave->num_samples*2);
    memcpy(ta.request.message.audio_data.audio.data.data(), wave->samples, wave->num_samples*2);
    delete_wave(wave);

    ros::service::call(transmit_audio_service_, ta);

    resp.success = ta.response.success;
    resp.error_message = ta.response.error_message;

    return true;
  }

  ros::NodeHandle node_handle_;
  cst_voice* voice_ = nullptr;
  ros::ServiceServer transmit_text_service_;

  std::string transmit_audio_service_ = "transmit_audio";

};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "send_text_service");

  TextToRadioTransmission service;

  ros::spin();


  return 0;
}


