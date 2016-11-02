
#ifndef GRGPK7FMC310_H
#define GRGPK7FMC310_H

#include <II_K7_310R/api.h>
#include <gnuradio/sync_block.h>
#include <boost/shared_ptr.hpp>

class ILoggerInterface
{
public:
    virtual ~ILoggerInterface()  {  }

    virtual void  Log(const std::string & a_string) = 0;
    virtual void  DebugLog(const std::string & a_string) = 0;
};

class LibraryIo;

class GRGpK7Fmc310
{
public:
    GRGpK7Fmc310(ILoggerInterface *Logger);
    ~GRGpK7Fmc310();

    // Settings

    struct GpDspSettings {
        GpDspSettings() {};
        GpDspSettings(float rf_gain, unsigned short  trigger_source,
                      const char* ddc_filter_path, bool is_rf_tuner,
                      float rf_center_freq, short max_channels,
                      float ch0_offset_freq, float ch1_offset_freq, float ch2_offset_freq, float ch3_offset_freq,
                      float ch4_offset_freq, float ch5_offset_freq, float ch6_offset_freq, float ch7_offset_freq,
                      float ch8_offset_freq, float ch9_offset_freq, float ch10_offset_freq, float ch11_offset_freq,
                      float ch12_offset_freq, float ch13_offset_freq, float ch14_offset_freq, float ch15_offset_freq,
                      unsigned short ch0_source, unsigned short ch1_source, unsigned short ch2_source, unsigned short ch3_source,
                      unsigned short ch4_source, unsigned short ch5_source, unsigned short ch6_source, unsigned short ch7_source,
                      unsigned short ch8_source, unsigned short ch9_source, unsigned short ch10_source, unsigned short ch11_source,
                      unsigned short ch12_source, unsigned short ch13_source, unsigned short ch14_source, unsigned short ch15_source
            ) :
            RfGain(rf_gain),
            TriggerSource(trigger_source),
            DdcFilterPath(ddc_filter_path),  // labeled as "DDC Bandwidth" in GR block
            IsRfTuner(is_rf_tuner),
            RfCenterFreq(rf_center_freq),
            MaxChannels(max_channels)
          // warning: extended initializer lists only available with -std=c++11 or -std=gnu++11:
//            ChOffsetFreq{ch0_offset_freq, ch1_offset_freq, ch2_offset_freq, ch3_offset_freq,
//                         ch4_offset_freq, ch5_offset_freq, ch6_offset_freq, ch7_offset_freq,
//                         ch8_offset_freq, ch9_offset_freq, ch10_offset_freq, ch11_offset_freq,
//                         ch12_offset_freq, ch13_offset_freq, ch14_offset_freq, ch15_offset_freq}
        {
            ChOffsetFreq[0] = ch0_offset_freq;
            ChOffsetFreq[1] = ch1_offset_freq;
            ChOffsetFreq[2] = ch2_offset_freq;
            ChOffsetFreq[3] = ch3_offset_freq;
            ChOffsetFreq[4] = ch4_offset_freq;
            ChOffsetFreq[5] = ch5_offset_freq;
            ChOffsetFreq[6] = ch6_offset_freq;
            ChOffsetFreq[7] = ch7_offset_freq;
            ChOffsetFreq[8] = ch8_offset_freq;
            ChOffsetFreq[9] = ch9_offset_freq;
            ChOffsetFreq[10] = ch10_offset_freq;
            ChOffsetFreq[11] = ch11_offset_freq;
            ChOffsetFreq[12] = ch12_offset_freq;
            ChOffsetFreq[13] = ch13_offset_freq;
            ChOffsetFreq[14] = ch14_offset_freq;
            ChOffsetFreq[15] = ch15_offset_freq;
            ChSource[0] = ch0_source;
            ChSource[1] = ch1_source;
            ChSource[2] = ch2_source;
            ChSource[3] = ch3_source;
            ChSource[4] = ch4_source;
            ChSource[5] = ch5_source;
            ChSource[6] = ch6_source;
            ChSource[7] = ch7_source;
            ChSource[8] = ch8_source;
            ChSource[9] = ch9_source;
            ChSource[10] = ch10_source;
            ChSource[11] = ch11_source;
            ChSource[12] = ch12_source;
            ChSource[13] = ch13_source;
            ChSource[14] = ch14_source;
            ChSource[15] = ch15_source;
        }
        float  RfGain;
        unsigned short  TriggerSource;
        const char*  DdcFilterPath;
        bool  IsRfTuner;
        float  RfCenterFreq;
        short  MaxChannels;
        float  ChOffsetFreq[16];
        unsigned short ChSource[16];
    };
    void SetSettings(const GpDspSettings& settings);
    bool IsDdc() const { return IsDdcFlag; }

    struct GpFftSettings {
        GpFftSettings() {};
        GpFftSettings(unsigned short fft0_source, unsigned short  fft0_windowing, bool is_fft0_fasd, float fft0_fasd
                      ) :
            Fft0Source(fft0_source),
            Fft0Windowing(fft0_windowing),
            IsFft0Fasd(is_fft0_fasd),
            Fft0Fasd(fft0_fasd)
        {}
        unsigned short  Fft0Source;
        unsigned short  Fft0Windowing;
        bool  IsFft0Fasd;
        float Fft0Fasd;
    };
    void SetFftSettings(const GpFftSettings& settings);
    bool IsFft() const { return IsFftFlag; }

    // Requires hardware:
    void  OpenDriver();
    bool  Start();
    bool  Stop();

    int Work(int noutput_items,
             gr_vector_const_void_star &input_items,
             gr_vector_void_star &output_items);

    int FftWork(int noutput_items,
             gr_vector_const_void_star &input_items,
             gr_vector_void_star &output_items);


private:
    // LibraryIo  *Io;
    // typedef boost::shared_ptr<LibraryIo> LibIoPtr;
    typedef LibraryIo* LibIoPtr;
    static LibIoPtr  Io;
    static bool  IsOpenFlag;
    static bool  IsStreamingFlag;
    static bool  IsDdcFlag;
    static bool  IsFftFlag;
};

#endif // GRGPK7FMC310_H
