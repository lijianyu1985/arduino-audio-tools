/**
 * @file player-sd-audiokit.ino
 * @brief see https://github.com/pschatzmann/arduino-audio-tools/blob/main/examples/examples-audiokit/player-sdmmc-audiokit/README.md
 * Make sure that the pins are set to on, on, on, on, on
 * @author Phil Schatzmann
 * @copyright GPLv3
 */

#include "AudioTools.h"
#include "AudioLibs/AudioKit.h"
#include "AudioLibs/AudioSourceSdMmc.h"
#include "AudioCodecs/CodecMP3Helix.h"

const char *startFilePath = "/";
const char* ext="mp3";
AudioSourceSdMmc source(startFilePath, ext);
AudioKitStream kit;
MP3DecoderHelix decoder;  // or change to MP3DecoderMAD
AudioPlayer player(source, kit, decoder);
 

void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  // setup output
  auto cfg = kit.defaultConfig(TX_MODE);
  cfg.sd_active = false;
  kit.begin(cfg);


  // setup player
  player.setVolume(0.9);
  player.begin();
  player.setAutoNext(false);

  // select file with setPath() or setIndex()
  //player.setPath("/ZZ Top/Unknown Album/Lowrider.mp3");
  //player.setIndex(1); // 2nd file
  player.setPath("/mp3_128.mp3");
}

void loop() {
  player.copy();
}
