#pragma once
#include <knx.h>

// Parameter with single occurance

#define LOG_NumChannels                0      // uint8_t
#define LOG_StartupDelayBase           1      // 2 Bits, Bit 7-6
#define     LOG_StartupDelayBaseMask 0xC0
#define     LOG_StartupDelayBaseShift 6
#define LOG_StartupDelayTime           1      // uint14_t
#define LOG_HeartbeatDelayBase         3      // 2 Bits, Bit 7-6
#define     LOG_HeartbeatDelayBaseMask 0xC0
#define     LOG_HeartbeatDelayBaseShift 6
#define LOG_HeartbeatDelayTime         3      // uint14_t
#define LOG_ReadTimeDate               5      // 1 Bit, Bit 7
#define     LOG_ReadTimeDateMask 0x80
#define     LOG_ReadTimeDateShift 7
#define LOG_BuzzerInstalled            5      // 1 Bit, Bit 6
#define     LOG_BuzzerInstalledMask 0x40
#define     LOG_BuzzerInstalledShift 6
#define LOG_LedInstalled               5      // 1 Bit, Bit 5
#define     LOG_LedInstalledMask 0x20
#define     LOG_LedInstalledShift 5
#define LOG_EepromInstalled            5      // 1 Bit, Bit 4
#define     LOG_EepromInstalledMask 0x10
#define     LOG_EepromInstalledShift 4
#define LOG_VacationKo                 5      // 1 Bit, Bit 2
#define     LOG_VacationKoMask 0x04
#define     LOG_VacationKoShift 2
#define LOG_HolidayKo                  5      // 1 Bit, Bit 1
#define     LOG_HolidayKoMask 0x02
#define     LOG_HolidayKoShift 1
#define LOG_VacationRead               5      // 1 Bit, Bit 0
#define     LOG_VacationReadMask 0x01
#define     LOG_VacationReadShift 0
#define LOG_HolidaySend                6      // 1 Bit, Bit 7
#define     LOG_HolidaySendMask 0x80
#define     LOG_HolidaySendShift 7
#define LOG_Timezone                   6      // 2 Bits, Bit 6-5
#define     LOG_TimezoneMask 0x60
#define     LOG_TimezoneShift 5
#define LOG_UseSummertime              6      // 1 Bit, Bit 4
#define     LOG_UseSummertimeMask 0x10
#define     LOG_UseSummertimeShift 4
#define LOG_Diagnose                   6      // 1 Bit, Bit 3
#define     LOG_DiagnoseMask 0x08
#define     LOG_DiagnoseShift 3
#define LOG_Watchdog                   6      // 1 Bit, Bit 2
#define     LOG_WatchdogMask 0x04
#define     LOG_WatchdogShift 2
#define LOG_Neujahr                    7      // 1 Bit, Bit 7
#define     LOG_NeujahrMask 0x80
#define     LOG_NeujahrShift 7
#define LOG_DreiKoenige                7      // 1 Bit, Bit 6
#define     LOG_DreiKoenigeMask 0x40
#define     LOG_DreiKoenigeShift 6
#define LOG_Weiberfastnacht            7      // 1 Bit, Bit 5
#define     LOG_WeiberfastnachtMask 0x20
#define     LOG_WeiberfastnachtShift 5
#define LOG_Rosenmontag                7      // 1 Bit, Bit 4
#define     LOG_RosenmontagMask 0x10
#define     LOG_RosenmontagShift 4
#define LOG_Fastnachtsdienstag         7      // 1 Bit, Bit 3
#define     LOG_FastnachtsdienstagMask 0x08
#define     LOG_FastnachtsdienstagShift 3
#define LOG_Aschermittwoch             7      // 1 Bit, Bit 2
#define     LOG_AschermittwochMask 0x04
#define     LOG_AschermittwochShift 2
#define LOG_Gruendonnerstag            7      // 1 Bit, Bit 1
#define     LOG_GruendonnerstagMask 0x02
#define     LOG_GruendonnerstagShift 1
#define LOG_Karfreitag                 7      // 1 Bit, Bit 0
#define     LOG_KarfreitagMask 0x01
#define     LOG_KarfreitagShift 0
#define LOG_Ostersonntag               8      // 1 Bit, Bit 7
#define     LOG_OstersonntagMask 0x80
#define     LOG_OstersonntagShift 7
#define LOG_Ostermontag                8      // 1 Bit, Bit 6
#define     LOG_OstermontagMask 0x40
#define     LOG_OstermontagShift 6
#define LOG_TagDerArbeit               8      // 1 Bit, Bit 5
#define     LOG_TagDerArbeitMask 0x20
#define     LOG_TagDerArbeitShift 5
#define LOG_Himmelfahrt                8      // 1 Bit, Bit 4
#define     LOG_HimmelfahrtMask 0x10
#define     LOG_HimmelfahrtShift 4
#define LOG_Pfingstsonntag             8      // 1 Bit, Bit 3
#define     LOG_PfingstsonntagMask 0x08
#define     LOG_PfingstsonntagShift 3
#define LOG_Pfingstmontag              8      // 1 Bit, Bit 2
#define     LOG_PfingstmontagMask 0x04
#define     LOG_PfingstmontagShift 2
#define LOG_Frohleichnam               8      // 1 Bit, Bit 1
#define     LOG_FrohleichnamMask 0x02
#define     LOG_FrohleichnamShift 1
#define LOG_Friedensfest               8      // 1 Bit, Bit 0
#define     LOG_FriedensfestMask 0x01
#define     LOG_FriedensfestShift 0
#define LOG_MariaHimmelfahrt           9      // 1 Bit, Bit 7
#define     LOG_MariaHimmelfahrtMask 0x80
#define     LOG_MariaHimmelfahrtShift 7
#define LOG_DeutscheEinheit            9      // 1 Bit, Bit 6
#define     LOG_DeutscheEinheitMask 0x40
#define     LOG_DeutscheEinheitShift 6
#define LOG_Reformationstag            9      // 1 Bit, Bit 5
#define     LOG_ReformationstagMask 0x20
#define     LOG_ReformationstagShift 5
#define LOG_Allerheiligen              9      // 1 Bit, Bit 4
#define     LOG_AllerheiligenMask 0x10
#define     LOG_AllerheiligenShift 4
#define LOG_BussBettag                 9      // 1 Bit, Bit 3
#define     LOG_BussBettagMask 0x08
#define     LOG_BussBettagShift 3
#define LOG_Advent1                    9      // 1 Bit, Bit 2
#define     LOG_Advent1Mask 0x04
#define     LOG_Advent1Shift 2
#define LOG_Advent2                    9      // 1 Bit, Bit 1
#define     LOG_Advent2Mask 0x02
#define     LOG_Advent2Shift 1
#define LOG_Advent3                    9      // 1 Bit, Bit 0
#define     LOG_Advent3Mask 0x01
#define     LOG_Advent3Shift 0
#define LOG_Advent4                   10      // 1 Bit, Bit 7
#define     LOG_Advent4Mask 0x80
#define     LOG_Advent4Shift 7
#define LOG_Heiligabend               10      // 1 Bit, Bit 6
#define     LOG_HeiligabendMask 0x40
#define     LOG_HeiligabendShift 6
#define LOG_Weihnachtstag1            10      // 1 Bit, Bit 5
#define     LOG_Weihnachtstag1Mask 0x20
#define     LOG_Weihnachtstag1Shift 5
#define LOG_Weihnachtstag2            10      // 1 Bit, Bit 4
#define     LOG_Weihnachtstag2Mask 0x10
#define     LOG_Weihnachtstag2Shift 4
#define LOG_Silvester                 10      // 1 Bit, Bit 3
#define     LOG_SilvesterMask 0x08
#define     LOG_SilvesterShift 3
#define LOG_Latitude                  11      // float
#define LOG_Longitude                 15      // float
#define LOG_BuzzerSilent              19      // uint16_t
#define LOG_BuzzerNormal              21      // uint16_t
#define LOG_BuzzerLoud                23      // uint16_t
#define LOG_LedMapping                25      // 3 Bits, Bit 7-5
#define     LOG_LedMappingMask 0xE0
#define     LOG_LedMappingShift 5

#define LOG_KoHeartbeat 1
#define LOG_KoTime 2
#define LOG_KoDate 3
#define LOG_KoVacation 4
#define LOG_KoHoliday1 5
#define LOG_KoHoliday2 6
#define LOG_KoDiagnose 7
#define LOG_KoLedLock 8
#define LOG_KoBuzzerLock 9

#define PM_PMChannels                40      // uint8_t
#define PM_HardwarePM                41      // 1 Bit, Bit 7
#define     PM_HardwarePMMask 0x80
#define     PM_HardwarePMShift 7
#define PM_SendPresence              41      // 1 Bit, Bit 6
#define     PM_SendPresenceMask 0x40
#define     PM_SendPresenceShift 6
#define PM_LEDRot                    41      // 2 Bits, Bit 5-4
#define     PM_LEDRotMask 0x30
#define     PM_LEDRotShift 4
#define PM_LEDOrange                 41      // 2 Bits, Bit 3-2
#define     PM_LEDOrangeMask 0x0C
#define     PM_LEDOrangeShift 2
#define PM_LuxOffsetPM               42      // int8_t
#define PM_LuxSendDelta              43      // uint16_t
#define PM_LuxSendCycleDelayBase     46      // 2 Bits, Bit 7-6
#define     PM_LuxSendCycleDelayBaseMask 0xC0
#define     PM_LuxSendCycleDelayBaseShift 6
#define PM_LuxSendCycleDelayTime     46      // uint14_t

#define PM_KoLuxOut 20
#define PM_KoPresenceOut 21
#define PM_KoMoveOut 22
#define PM_KoMoveSpeedOut 23
#define PM_KoLEDPresence 24
#define PM_KoLEDMove 25
#define PM_KoScenario 26
#define PM_KoSensitivity 27
#define PM_KoHfReset 28

#define LOG_ChannelCount 30

// Parameter per channel
#define LOG_ParamBlockOffset 48
#define LOG_ParamBlockSize 87
#define LOG_fChannelDelayBase          0      // 2 Bits, Bit 7-6
#define     LOG_fChannelDelayBaseMask 0xC0
#define     LOG_fChannelDelayBaseShift 6
#define LOG_fChannelDelayTime          0      // uint14_t
#define LOG_fLogic                     2      // 8 Bits, Bit 7-0
#define LOG_fCalculate                 3      // 2 Bits, Bit 1-0
#define     LOG_fCalculateMask 0x03
#define     LOG_fCalculateShift 0
#define LOG_fDisable                   3      // 1 Bit, Bit 2
#define     LOG_fDisableMask 0x04
#define     LOG_fDisableShift 2
#define LOG_fAlarm                     3      // 1 Bit, Bit 3
#define     LOG_fAlarmMask 0x08
#define     LOG_fAlarmShift 3
#define LOG_fTrigger                   4      // 8 Bits, Bit 7-0
#define LOG_fTriggerE1                 4      // 1 Bit, Bit 0
#define     LOG_fTriggerE1Mask 0x01
#define     LOG_fTriggerE1Shift 0
#define LOG_fTriggerE2                 4      // 1 Bit, Bit 1
#define     LOG_fTriggerE2Mask 0x02
#define     LOG_fTriggerE2Shift 1
#define LOG_fTriggerI1                 4      // 1 Bit, Bit 2
#define     LOG_fTriggerI1Mask 0x04
#define     LOG_fTriggerI1Shift 2
#define LOG_fTriggerI2                 4      // 1 Bit, Bit 3
#define     LOG_fTriggerI2Mask 0x08
#define     LOG_fTriggerI2Shift 3
#define LOG_fTriggerTime               4      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateClose          5      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateOpen           6      // 8 Bits, Bit 7-0
#define LOG_fE1                        7      // 4 Bits, Bit 3-0
#define     LOG_fE1Mask 0x0F
#define     LOG_fE1Shift 0
#define LOG_fE1Convert                 7      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertMask 0xF0
#define     LOG_fE1ConvertShift 4
#define LOG_fE1ConvertFloat            7      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertFloatMask 0xF0
#define     LOG_fE1ConvertFloatShift 4
#define LOG_fE1ConvertSpecial          7      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertSpecialMask 0xF0
#define     LOG_fE1ConvertSpecialShift 4
#define LOG_fE1Dpt                     8      // 8 Bits, Bit 7-0
#define LOG_fE1Default                 9      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultMask 0x03
#define     LOG_fE1DefaultShift 0
#define LOG_fE1DefaultExt              9      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultExtMask 0x03
#define     LOG_fE1DefaultExtShift 0
#define LOG_fE1DefaultEEPROM           9      // 1 Bit, Bit 2
#define     LOG_fE1DefaultEEPROMMask 0x04
#define     LOG_fE1DefaultEEPROMShift 2
#define LOG_fE1DefaultRepeat           9      // 1 Bit, Bit 3
#define     LOG_fE1DefaultRepeatMask 0x08
#define     LOG_fE1DefaultRepeatShift 3
#define LOG_fTYearDay                  9      // 1 Bit, Bit 4
#define     LOG_fTYearDayMask 0x10
#define     LOG_fTYearDayShift 4
#define LOG_fTRestoreState             9      // 2 Bits, Bit 6-5
#define     LOG_fTRestoreStateMask 0x60
#define     LOG_fTRestoreStateShift 5
#define LOG_fE1RepeatBase             10      // 2 Bits, Bit 7-6
#define     LOG_fE1RepeatBaseMask 0xC0
#define     LOG_fE1RepeatBaseShift 6
#define LOG_fE1RepeatTime             10      // uint14_t
#define LOG_fE2                       12      // 4 Bits, Bit 3-0
#define     LOG_fE2Mask 0x0F
#define     LOG_fE2Shift 0
#define LOG_fE2Convert                12      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertMask 0xF0
#define     LOG_fE2ConvertShift 4
#define LOG_fE2ConvertFloat           12      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertFloatMask 0xF0
#define     LOG_fE2ConvertFloatShift 4
#define LOG_fE2ConvertSpecial         12      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertSpecialMask 0xF0
#define     LOG_fE2ConvertSpecialShift 4
#define LOG_fE2Dpt                    13      // 8 Bits, Bit 7-0
#define LOG_fE2Default                14      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultMask 0x03
#define     LOG_fE2DefaultShift 0
#define LOG_fE2DefaultExt             14      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultExtMask 0x03
#define     LOG_fE2DefaultExtShift 0
#define LOG_fE2DefaultEEPROM          14      // 1 Bit, Bit 2
#define     LOG_fE2DefaultEEPROMMask 0x04
#define     LOG_fE2DefaultEEPROMShift 2
#define LOG_fE2DefaultRepeat          14      // 1 Bit, Bit 3
#define     LOG_fE2DefaultRepeatMask 0x08
#define     LOG_fE2DefaultRepeatShift 3
#define LOG_fTHoliday                 14      // 2 Bits, Bit 4-3
#define     LOG_fTHolidayMask 0x18
#define     LOG_fTHolidayShift 3
#define LOG_fTVacation                14      // 2 Bits, Bit 6-5
#define     LOG_fTVacationMask 0x60
#define     LOG_fTVacationShift 5
#define LOG_fE2RepeatBase             15      // 2 Bits, Bit 7-6
#define     LOG_fE2RepeatBaseMask 0xC0
#define     LOG_fE2RepeatBaseShift 6
#define LOG_fE2RepeatTime             15      // uint14_t
#define LOG_fTd1DuskDawn              15      // 4 Bits, Bit 7-4
#define     LOG_fTd1DuskDawnMask 0xF0
#define     LOG_fTd1DuskDawnShift 4
#define LOG_fTd2DuskDawn              15      // 4 Bits, Bit 3-0
#define     LOG_fTd2DuskDawnMask 0x0F
#define     LOG_fTd2DuskDawnShift 0
#define LOG_fTd3DuskDawn              16      // 4 Bits, Bit 7-4
#define     LOG_fTd3DuskDawnMask 0xF0
#define     LOG_fTd3DuskDawnShift 4
#define LOG_fTd4DuskDawn              16      // 4 Bits, Bit 3-0
#define     LOG_fTd4DuskDawnMask 0x0F
#define     LOG_fTd4DuskDawnShift 0
#define LOG_fTd5DuskDawn              17      // 4 Bits, Bit 7-4
#define     LOG_fTd5DuskDawnMask 0xF0
#define     LOG_fTd5DuskDawnShift 4
#define LOG_fTd6DuskDawn              17      // 4 Bits, Bit 3-0
#define     LOG_fTd6DuskDawnMask 0x0F
#define     LOG_fTd6DuskDawnShift 0
#define LOG_fTd7DuskDawn              18      // 4 Bits, Bit 7-4
#define     LOG_fTd7DuskDawnMask 0xF0
#define     LOG_fTd7DuskDawnShift 4
#define LOG_fTd8DuskDawn              18      // 4 Bits, Bit 3-0
#define     LOG_fTd8DuskDawnMask 0x0F
#define     LOG_fTd8DuskDawnShift 0
#define LOG_fE1LowDelta               19      // int32_t
#define LOG_fE1HighDelta              23      // int32_t
#define LOG_fE1LowDeltaFloat          19      // float
#define LOG_fE1HighDeltaFloat         23      // float
#define LOG_fE1Low0Valid              26      // 1 Bit, Bit 7
#define     LOG_fE1Low0ValidMask 0x80
#define     LOG_fE1Low0ValidShift 7
#define LOG_fE1Low1Valid              26      // 1 Bit, Bit 6
#define     LOG_fE1Low1ValidMask 0x40
#define     LOG_fE1Low1ValidShift 6
#define LOG_fE1Low2Valid              26      // 1 Bit, Bit 5
#define     LOG_fE1Low2ValidMask 0x20
#define     LOG_fE1Low2ValidShift 5
#define LOG_fE1Low3Valid              26      // 1 Bit, Bit 4
#define     LOG_fE1Low3ValidMask 0x10
#define     LOG_fE1Low3ValidShift 4
#define LOG_fE1Low4Valid              26      // 1 Bit, Bit 3
#define     LOG_fE1Low4ValidMask 0x08
#define     LOG_fE1Low4ValidShift 3
#define LOG_fE1Low5Valid              26      // 1 Bit, Bit 2
#define     LOG_fE1Low5ValidMask 0x04
#define     LOG_fE1Low5ValidShift 2
#define LOG_fE1Low6Valid              26      // 1 Bit, Bit 1
#define     LOG_fE1Low6ValidMask 0x02
#define     LOG_fE1Low6ValidShift 1
#define LOG_fE1Low7Valid              26      // 1 Bit, Bit 0
#define     LOG_fE1Low7ValidMask 0x01
#define     LOG_fE1Low7ValidShift 0
#define LOG_fE1LowDpt2                19      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt2               20      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt2               21      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt2               22      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt2Fix             19      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt5                19      // uint8_t
#define LOG_fE1HighDpt5               23      // uint8_t
#define LOG_fE1Low0Dpt5In             19      // uint8_t
#define LOG_fE1Low1Dpt5In             20      // uint8_t
#define LOG_fE1Low2Dpt5In             21      // uint8_t
#define LOG_fE1Low3Dpt5In             22      // uint8_t
#define LOG_fE1Low4Dpt5In             23      // uint8_t
#define LOG_fE1Low5Dpt5In             24      // uint8_t
#define LOG_fE1Low6Dpt5In             25      // uint8_t
#define LOG_fE1LowDpt5Fix             19      // uint8_t
#define LOG_fE1LowDpt5001             19      // uint8_t
#define LOG_fE1HighDpt5001            23      // uint8_t
#define LOG_fE1Low0Dpt5xIn            19      // uint8_t
#define LOG_fE1Low1Dpt5xIn            20      // uint8_t
#define LOG_fE1Low2Dpt5xIn            21      // uint8_t
#define LOG_fE1Low3Dpt5xIn            22      // uint8_t
#define LOG_fE1Low4Dpt5xIn            23      // uint8_t
#define LOG_fE1Low5Dpt5xIn            24      // uint8_t
#define LOG_fE1Low6Dpt5xIn            25      // uint8_t
#define LOG_fE1LowDpt5xFix            19      // uint8_t
#define LOG_fE1LowDpt6                19      // int8_t
#define LOG_fE1HighDpt6               23      // int8_t
#define LOG_fE1Low0Dpt6In             19      // int8_t
#define LOG_fE1Low1Dpt6In             20      // int8_t
#define LOG_fE1Low2Dpt6In             21      // int8_t
#define LOG_fE1Low3Dpt6In             22      // int8_t
#define LOG_fE1Low4Dpt6In             23      // int8_t
#define LOG_fE1Low5Dpt6In             24      // int8_t
#define LOG_fE1Low6Dpt6In             25      // int8_t
#define LOG_fE1LowDpt6Fix             19      // int8_t
#define LOG_fE1LowDpt7                19      // uint16_t
#define LOG_fE1HighDpt7               23      // uint16_t
#define LOG_fE1Low0Dpt7In             19      // uint16_t
#define LOG_fE1Low1Dpt7In             21      // uint16_t
#define LOG_fE1Low2Dpt7In             23      // uint16_t
#define LOG_fE1LowDpt7Fix             19      // uint16_t
#define LOG_fE1LowDpt8                19      // int16_t
#define LOG_fE1HighDpt8               23      // int16_t
#define LOG_fE1Low0Dpt8In             19      // int16_t
#define LOG_fE1Low1Dpt8In             21      // int16_t
#define LOG_fE1Low2Dpt8In             23      // int16_t
#define LOG_fE1LowDpt8Fix             19      // int16_t
#define LOG_fE1LowDpt9                19      // float
#define LOG_fE1HighDpt9               23      // float
#define LOG_fE1LowDpt9Fix             19      // float
#define LOG_fE1Low0Dpt17              19      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt17              20      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt17              21      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt17              22      // 8 Bits, Bit 7-0
#define LOG_fE1Low4Dpt17              23      // 8 Bits, Bit 7-0
#define LOG_fE1Low5Dpt17              24      // 8 Bits, Bit 7-0
#define LOG_fE1Low6Dpt17              25      // 8 Bits, Bit 7-0
#define LOG_fE1Low7Dpt17              26      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt17Fix            19      // 8 Bits, Bit 7-0
#define LOG_fE1LowDptRGB              19      // int32_t
#define LOG_fE1HighDptRGB             23      // int32_t
#define LOG_fE1LowDptRGBFix           19      // int32_t
#define LOG_fE2LowDelta               27      // int32_t
#define LOG_fE2HighDelta              31      // int32_t
#define LOG_fE2LowDeltaFloat          27      // float
#define LOG_fE2HighDeltaFloat         31      // float
#define LOG_fE2Low0Valid              34      // 1 Bit, Bit 7
#define     LOG_fE2Low0ValidMask 0x80
#define     LOG_fE2Low0ValidShift 7
#define LOG_fE2Low1Valid              34      // 1 Bit, Bit 6
#define     LOG_fE2Low1ValidMask 0x40
#define     LOG_fE2Low1ValidShift 6
#define LOG_fE2Low2Valid              34      // 1 Bit, Bit 5
#define     LOG_fE2Low2ValidMask 0x20
#define     LOG_fE2Low2ValidShift 5
#define LOG_fE2Low3Valid              34      // 1 Bit, Bit 4
#define     LOG_fE2Low3ValidMask 0x10
#define     LOG_fE2Low3ValidShift 4
#define LOG_fE2Low4Valid              34      // 1 Bit, Bit 3
#define     LOG_fE2Low4ValidMask 0x08
#define     LOG_fE2Low4ValidShift 3
#define LOG_fE2Low5Valid              34      // 1 Bit, Bit 2
#define     LOG_fE2Low5ValidMask 0x04
#define     LOG_fE2Low5ValidShift 2
#define LOG_fE2Low6Valid              34      // 1 Bit, Bit 1
#define     LOG_fE2Low6ValidMask 0x02
#define     LOG_fE2Low6ValidShift 1
#define LOG_fE2Low7Valid              34      // 1 Bit, Bit 0
#define     LOG_fE2Low7ValidMask 0x01
#define     LOG_fE2Low7ValidShift 0
#define LOG_fE2Low0Dpt2               27      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt2               28      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt2               29      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt2               30      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt2Fix             27      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt5                27      // uint8_t
#define LOG_fE2HighDpt5               31      // uint8_t
#define LOG_fE2Low0Dpt5In             27      // uint8_t
#define LOG_fE2Low1Dpt5In             28      // uint8_t
#define LOG_fE2Low2Dpt5In             29      // uint8_t
#define LOG_fE2Low3Dpt5In             30      // uint8_t
#define LOG_fE2Low4Dpt5In             31      // uint8_t
#define LOG_fE2Low5Dpt5In             32      // uint8_t
#define LOG_fE2Low6Dpt5In             33      // uint8_t
#define LOG_fE2LowDpt5Fix             27      // uint8_t
#define LOG_fE2LowDpt5001             27      // uint8_t
#define LOG_fE2HighDpt5001            31      // uint8_t
#define LOG_fE2Low0Dpt5xIn            27      // uint8_t
#define LOG_fE2Low1Dpt5xIn            28      // uint8_t
#define LOG_fE2Low2Dpt5xIn            29      // uint8_t
#define LOG_fE2Low3Dpt5xIn            30      // uint8_t
#define LOG_fE2Low4Dpt5xIn            31      // uint8_t
#define LOG_fE2Low5Dpt5xIn            32      // uint8_t
#define LOG_fE2Low6Dpt5xIn            33      // uint8_t
#define LOG_fE2LowDpt5xFix            27      // uint8_t
#define LOG_fE2LowDpt6                27      // int8_t
#define LOG_fE2HighDpt6               31      // int8_t
#define LOG_fE2Low0Dpt6In             27      // int8_t
#define LOG_fE2Low1Dpt6In             28      // int8_t
#define LOG_fE2Low2Dpt6In             29      // int8_t
#define LOG_fE2Low3Dpt6In             30      // int8_t
#define LOG_fE2Low4Dpt6In             31      // int8_t
#define LOG_fE2Low5Dpt6In             32      // int8_t
#define LOG_fE2Low6Dpt6In             33      // int8_t
#define LOG_fE2LowDpt6Fix             27      // int8_t
#define LOG_fE2LowDpt7                27      // uint16_t
#define LOG_fE2HighDpt7               31      // uint16_t
#define LOG_fE2Low0Dpt7In             27      // uint16_t
#define LOG_fE2Low1Dpt7In             29      // uint16_t
#define LOG_fE2Low2Dpt7In             31      // uint16_t
#define LOG_fE2LowDpt7Fix             27      // uint16_t
#define LOG_fE2LowDpt8                27      // int16_t
#define LOG_fE2HighDpt8               31      // int16_t
#define LOG_fE2Low0Dpt8In             27      // int16_t
#define LOG_fE2Low1Dpt8In             29      // int16_t
#define LOG_fE2Low2Dpt8In             31      // int16_t
#define LOG_fE2LowDpt8Fix             27      // int16_t
#define LOG_fE2LowDpt9                27      // float
#define LOG_fE2HighDpt9               31      // float
#define LOG_fE2LowDpt9Fix             27      // float
#define LOG_fE2Low0Dpt17              27      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt17              28      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt17              29      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt17              30      // 8 Bits, Bit 7-0
#define LOG_fE2Low4Dpt17              31      // 8 Bits, Bit 7-0
#define LOG_fE2Low5Dpt17              32      // 8 Bits, Bit 7-0
#define LOG_fE2Low6Dpt17              33      // 8 Bits, Bit 7-0
#define LOG_fE2Low7Dpt17              34      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt17Fix            27      // 8 Bits, Bit 7-0
#define LOG_fE2LowDptRGB              27      // int32_t
#define LOG_fE2HighDptRGB             31      // int32_t
#define LOG_fE2LowDptRGBFix           27      // int32_t
#define LOG_fTd1Value                 19      // 1 Bit, Bit 7
#define     LOG_fTd1ValueMask 0x80
#define     LOG_fTd1ValueShift 7
#define LOG_fTd1HourAbs               19      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourAbsMask 0x3E
#define     LOG_fTd1HourAbsShift 1
#define LOG_fTd1HourRel               19      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourRelMask 0x3E
#define     LOG_fTd1HourRelShift 1
#define LOG_fTd1MinuteAbs             19      // 6 Bits, Bit 0--5
#define LOG_fTd1MinuteRel             19      // 6 Bits, Bit 0--5
#define LOG_fTd1Weekday               20      // 3 Bits, Bit 2-0
#define     LOG_fTd1WeekdayMask 0x07
#define     LOG_fTd1WeekdayShift 0
#define LOG_fTd2Value                 21      // 1 Bit, Bit 7
#define     LOG_fTd2ValueMask 0x80
#define     LOG_fTd2ValueShift 7
#define LOG_fTd2HourAbs               21      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourAbsMask 0x3E
#define     LOG_fTd2HourAbsShift 1
#define LOG_fTd2HourRel               21      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourRelMask 0x3E
#define     LOG_fTd2HourRelShift 1
#define LOG_fTd2MinuteAbs             21      // 6 Bits, Bit 0--5
#define LOG_fTd2MinuteRel             21      // 6 Bits, Bit 0--5
#define LOG_fTd2Weekday               22      // 3 Bits, Bit 2-0
#define     LOG_fTd2WeekdayMask 0x07
#define     LOG_fTd2WeekdayShift 0
#define LOG_fTd3Value                 23      // 1 Bit, Bit 7
#define     LOG_fTd3ValueMask 0x80
#define     LOG_fTd3ValueShift 7
#define LOG_fTd3HourAbs               23      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourAbsMask 0x3E
#define     LOG_fTd3HourAbsShift 1
#define LOG_fTd3HourRel               23      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourRelMask 0x3E
#define     LOG_fTd3HourRelShift 1
#define LOG_fTd3MinuteAbs             23      // 6 Bits, Bit 0--5
#define LOG_fTd3MinuteRel             23      // 6 Bits, Bit 0--5
#define LOG_fTd3Weekday               24      // 3 Bits, Bit 2-0
#define     LOG_fTd3WeekdayMask 0x07
#define     LOG_fTd3WeekdayShift 0
#define LOG_fTd4Value                 25      // 1 Bit, Bit 7
#define     LOG_fTd4ValueMask 0x80
#define     LOG_fTd4ValueShift 7
#define LOG_fTd4HourAbs               25      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourAbsMask 0x3E
#define     LOG_fTd4HourAbsShift 1
#define LOG_fTd4HourRel               25      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourRelMask 0x3E
#define     LOG_fTd4HourRelShift 1
#define LOG_fTd4MinuteAbs             25      // 6 Bits, Bit 0--5
#define LOG_fTd4MinuteRel             25      // 6 Bits, Bit 0--5
#define LOG_fTd4Weekday               26      // 3 Bits, Bit 2-0
#define     LOG_fTd4WeekdayMask 0x07
#define     LOG_fTd4WeekdayShift 0
#define LOG_fTd5Value                 27      // 1 Bit, Bit 7
#define     LOG_fTd5ValueMask 0x80
#define     LOG_fTd5ValueShift 7
#define LOG_fTd5HourAbs               27      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourAbsMask 0x3E
#define     LOG_fTd5HourAbsShift 1
#define LOG_fTd5HourRel               27      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourRelMask 0x3E
#define     LOG_fTd5HourRelShift 1
#define LOG_fTd5MinuteAbs             27      // 6 Bits, Bit 0--5
#define LOG_fTd5MinuteRel             27      // 6 Bits, Bit 0--5
#define LOG_fTd5Weekday               28      // 3 Bits, Bit 2-0
#define     LOG_fTd5WeekdayMask 0x07
#define     LOG_fTd5WeekdayShift 0
#define LOG_fTd6Value                 29      // 1 Bit, Bit 7
#define     LOG_fTd6ValueMask 0x80
#define     LOG_fTd6ValueShift 7
#define LOG_fTd6HourAbs               29      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourAbsMask 0x3E
#define     LOG_fTd6HourAbsShift 1
#define LOG_fTd6HourRel               29      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourRelMask 0x3E
#define     LOG_fTd6HourRelShift 1
#define LOG_fTd6MinuteAbs             29      // 6 Bits, Bit 0--5
#define LOG_fTd6MinuteRel             29      // 6 Bits, Bit 0--5
#define LOG_fTd6Weekday               30      // 3 Bits, Bit 2-0
#define     LOG_fTd6WeekdayMask 0x07
#define     LOG_fTd6WeekdayShift 0
#define LOG_fTd7Value                 31      // 1 Bit, Bit 7
#define     LOG_fTd7ValueMask 0x80
#define     LOG_fTd7ValueShift 7
#define LOG_fTd7HourAbs               31      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourAbsMask 0x3E
#define     LOG_fTd7HourAbsShift 1
#define LOG_fTd7HourRel               31      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourRelMask 0x3E
#define     LOG_fTd7HourRelShift 1
#define LOG_fTd7MinuteAbs             31      // 6 Bits, Bit 0--5
#define LOG_fTd7MinuteRel             31      // 6 Bits, Bit 0--5
#define LOG_fTd7Weekday               32      // 3 Bits, Bit 2-0
#define     LOG_fTd7WeekdayMask 0x07
#define     LOG_fTd7WeekdayShift 0
#define LOG_fTd8Value                 33      // 1 Bit, Bit 7
#define     LOG_fTd8ValueMask 0x80
#define     LOG_fTd8ValueShift 7
#define LOG_fTd8HourAbs               33      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourAbsMask 0x3E
#define     LOG_fTd8HourAbsShift 1
#define LOG_fTd8HourRel               33      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourRelMask 0x3E
#define     LOG_fTd8HourRelShift 1
#define LOG_fTd8MinuteAbs             33      // 6 Bits, Bit 0--5
#define LOG_fTd8MinuteRel             33      // 6 Bits, Bit 0--5
#define LOG_fTd8Weekday               34      // 3 Bits, Bit 2-0
#define     LOG_fTd8WeekdayMask 0x07
#define     LOG_fTd8WeekdayShift 0
#define LOG_fTy1Weekday1              27      // 1 Bit, Bit 7
#define     LOG_fTy1Weekday1Mask 0x80
#define     LOG_fTy1Weekday1Shift 7
#define LOG_fTy1Weekday2              27      // 1 Bit, Bit 6
#define     LOG_fTy1Weekday2Mask 0x40
#define     LOG_fTy1Weekday2Shift 6
#define LOG_fTy1Weekday3              27      // 1 Bit, Bit 5
#define     LOG_fTy1Weekday3Mask 0x20
#define     LOG_fTy1Weekday3Shift 5
#define LOG_fTy1Weekday4              27      // 1 Bit, Bit 4
#define     LOG_fTy1Weekday4Mask 0x10
#define     LOG_fTy1Weekday4Shift 4
#define LOG_fTy1Weekday5              27      // 1 Bit, Bit 3
#define     LOG_fTy1Weekday5Mask 0x08
#define     LOG_fTy1Weekday5Shift 3
#define LOG_fTy1Weekday6              27      // 1 Bit, Bit 2
#define     LOG_fTy1Weekday6Mask 0x04
#define     LOG_fTy1Weekday6Shift 2
#define LOG_fTy1Weekday7              27      // 1 Bit, Bit 1
#define     LOG_fTy1Weekday7Mask 0x02
#define     LOG_fTy1Weekday7Shift 1
#define LOG_fTy1Day                   27      // 7 Bits, Bit 7-1
#define LOG_fTy1IsWeekday             27      // 1 Bit, Bit 0
#define     LOG_fTy1IsWeekdayMask 0x01
#define     LOG_fTy1IsWeekdayShift 0
#define LOG_fTy1Month                 28      // 4 Bits, Bit 7-4
#define     LOG_fTy1MonthMask 0xF0
#define     LOG_fTy1MonthShift 4
#define LOG_fTy2Weekday1              29      // 1 Bit, Bit 7
#define     LOG_fTy2Weekday1Mask 0x80
#define     LOG_fTy2Weekday1Shift 7
#define LOG_fTy2Weekday2              29      // 1 Bit, Bit 6
#define     LOG_fTy2Weekday2Mask 0x40
#define     LOG_fTy2Weekday2Shift 6
#define LOG_fTy2Weekday3              29      // 1 Bit, Bit 5
#define     LOG_fTy2Weekday3Mask 0x20
#define     LOG_fTy2Weekday3Shift 5
#define LOG_fTy2Weekday4              29      // 1 Bit, Bit 4
#define     LOG_fTy2Weekday4Mask 0x10
#define     LOG_fTy2Weekday4Shift 4
#define LOG_fTy2Weekday5              29      // 1 Bit, Bit 3
#define     LOG_fTy2Weekday5Mask 0x08
#define     LOG_fTy2Weekday5Shift 3
#define LOG_fTy2Weekday6              29      // 1 Bit, Bit 2
#define     LOG_fTy2Weekday6Mask 0x04
#define     LOG_fTy2Weekday6Shift 2
#define LOG_fTy2Weekday7              29      // 1 Bit, Bit 1
#define     LOG_fTy2Weekday7Mask 0x02
#define     LOG_fTy2Weekday7Shift 1
#define LOG_fTy2Day                   29      // 7 Bits, Bit 7-1
#define LOG_fTy2IsWeekday             29      // 1 Bit, Bit 0
#define     LOG_fTy2IsWeekdayMask 0x01
#define     LOG_fTy2IsWeekdayShift 0
#define LOG_fTy2Month                 30      // 4 Bits, Bit 7-4
#define     LOG_fTy2MonthMask 0xF0
#define     LOG_fTy2MonthShift 4
#define LOG_fTy3Weekday1              31      // 1 Bit, Bit 7
#define     LOG_fTy3Weekday1Mask 0x80
#define     LOG_fTy3Weekday1Shift 7
#define LOG_fTy3Weekday2              31      // 1 Bit, Bit 6
#define     LOG_fTy3Weekday2Mask 0x40
#define     LOG_fTy3Weekday2Shift 6
#define LOG_fTy3Weekday3              31      // 1 Bit, Bit 5
#define     LOG_fTy3Weekday3Mask 0x20
#define     LOG_fTy3Weekday3Shift 5
#define LOG_fTy3Weekday4              31      // 1 Bit, Bit 4
#define     LOG_fTy3Weekday4Mask 0x10
#define     LOG_fTy3Weekday4Shift 4
#define LOG_fTy3Weekday5              31      // 1 Bit, Bit 3
#define     LOG_fTy3Weekday5Mask 0x08
#define     LOG_fTy3Weekday5Shift 3
#define LOG_fTy3Weekday6              31      // 1 Bit, Bit 2
#define     LOG_fTy3Weekday6Mask 0x04
#define     LOG_fTy3Weekday6Shift 2
#define LOG_fTy3Weekday7              31      // 1 Bit, Bit 1
#define     LOG_fTy3Weekday7Mask 0x02
#define     LOG_fTy3Weekday7Shift 1
#define LOG_fTy3Day                   31      // 7 Bits, Bit 7-1
#define LOG_fTy3IsWeekday             31      // 1 Bit, Bit 0
#define     LOG_fTy3IsWeekdayMask 0x01
#define     LOG_fTy3IsWeekdayShift 0
#define LOG_fTy3Month                 32      // 4 Bits, Bit 7-4
#define     LOG_fTy3MonthMask 0xF0
#define     LOG_fTy3MonthShift 4
#define LOG_fTy4Weekday1              33      // 1 Bit, Bit 7
#define     LOG_fTy4Weekday1Mask 0x80
#define     LOG_fTy4Weekday1Shift 7
#define LOG_fTy4Weekday2              33      // 1 Bit, Bit 6
#define     LOG_fTy4Weekday2Mask 0x40
#define     LOG_fTy4Weekday2Shift 6
#define LOG_fTy4Weekday3              33      // 1 Bit, Bit 5
#define     LOG_fTy4Weekday3Mask 0x20
#define     LOG_fTy4Weekday3Shift 5
#define LOG_fTy4Weekday4              33      // 1 Bit, Bit 4
#define     LOG_fTy4Weekday4Mask 0x10
#define     LOG_fTy4Weekday4Shift 4
#define LOG_fTy4Weekday5              33      // 1 Bit, Bit 3
#define     LOG_fTy4Weekday5Mask 0x08
#define     LOG_fTy4Weekday5Shift 3
#define LOG_fTy4Weekday6              33      // 1 Bit, Bit 2
#define     LOG_fTy4Weekday6Mask 0x04
#define     LOG_fTy4Weekday6Shift 2
#define LOG_fTy4Weekday7              33      // 1 Bit, Bit 1
#define     LOG_fTy4Weekday7Mask 0x02
#define     LOG_fTy4Weekday7Shift 1
#define LOG_fTy4Day                   33      // 7 Bits, Bit 7-1
#define LOG_fTy4IsWeekday             33      // 1 Bit, Bit 0
#define     LOG_fTy4IsWeekdayMask 0x01
#define     LOG_fTy4IsWeekdayShift 0
#define LOG_fTy4Month                 34      // 4 Bits, Bit 7-4
#define     LOG_fTy4MonthMask 0xF0
#define     LOG_fTy4MonthShift 4
#define LOG_fI1                       35      // 4 Bits, Bit 7-4
#define     LOG_fI1Mask 0xF0
#define     LOG_fI1Shift 4
#define LOG_fI2                       35      // 4 Bits, Bit 3-0
#define     LOG_fI2Mask 0x0F
#define     LOG_fI2Shift 0
#define LOG_fI1Function               36      // uint8_t
#define LOG_fI2Function               37      // uint8_t
#define LOG_fOStairtimeBase           38      // 2 Bits, Bit 7-6
#define     LOG_fOStairtimeBaseMask 0xC0
#define     LOG_fOStairtimeBaseShift 6
#define LOG_fOStairtimeTime           38      // uint14_t
#define LOG_fOBlinkBase               40      // 2 Bits, Bit 7-6
#define     LOG_fOBlinkBaseMask 0xC0
#define     LOG_fOBlinkBaseShift 6
#define LOG_fOBlinkTime               40      // uint14_t
#define LOG_fODelay                   42      // 1 Bit, Bit 7
#define     LOG_fODelayMask 0x80
#define     LOG_fODelayShift 7
#define LOG_fODelayOnRepeat           42      // 2 Bits, Bit 6-5
#define     LOG_fODelayOnRepeatMask 0x60
#define     LOG_fODelayOnRepeatShift 5
#define LOG_fODelayOnReset            42      // 1 Bit, Bit 4
#define     LOG_fODelayOnResetMask 0x10
#define     LOG_fODelayOnResetShift 4
#define LOG_fODelayOffRepeat          42      // 2 Bits, Bit 3-2
#define     LOG_fODelayOffRepeatMask 0x0C
#define     LOG_fODelayOffRepeatShift 2
#define LOG_fODelayOffReset           42      // 1 Bit, Bit 1
#define     LOG_fODelayOffResetMask 0x02
#define     LOG_fODelayOffResetShift 1
#define LOG_fODelayOnBase             43      // 2 Bits, Bit 7-6
#define     LOG_fODelayOnBaseMask 0xC0
#define     LOG_fODelayOnBaseShift 6
#define LOG_fODelayOnTime             43      // uint14_t
#define LOG_fODelayOffBase            45      // 2 Bits, Bit 7-6
#define     LOG_fODelayOffBaseMask 0xC0
#define     LOG_fODelayOffBaseShift 6
#define LOG_fODelayOffTime            45      // uint14_t
#define LOG_fOStair                   47      // 1 Bit, Bit 7
#define     LOG_fOStairMask 0x80
#define     LOG_fOStairShift 7
#define LOG_fORetrigger               47      // 1 Bit, Bit 6
#define     LOG_fORetriggerMask 0x40
#define     LOG_fORetriggerShift 6
#define LOG_fOStairOff                47      // 1 Bit, Bit 5
#define     LOG_fOStairOffMask 0x20
#define     LOG_fOStairOffShift 5
#define LOG_fORepeat                  47      // 1 Bit, Bit 4
#define     LOG_fORepeatMask 0x10
#define     LOG_fORepeatShift 4
#define LOG_fOOutputFilter            47      // 2 Bits, Bit 3-2
#define     LOG_fOOutputFilterMask 0x0C
#define     LOG_fOOutputFilterShift 2
#define LOG_fORepeatOnBase            48      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOnBaseMask 0xC0
#define     LOG_fORepeatOnBaseShift 6
#define LOG_fORepeatOnTime            48      // uint14_t
#define LOG_fORepeatOffBase           50      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOffBaseMask 0xC0
#define     LOG_fORepeatOffBaseShift 6
#define LOG_fORepeatOffTime           50      // uint14_t
#define LOG_fODpt                     52      // 8 Bits, Bit 7-0
#define LOG_fOOn                      53      // 8 Bits, Bit 7-0
#define LOG_fOOnBuzzer                53      // 8 Bits, Bit 7-0
#define LOG_fOOnLed                   53      // 8 Bits, Bit 7-0
#define LOG_fOOnAll                   53      // 8 Bits, Bit 7-0
#define LOG_fOOnTone                  54      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt1                  54      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt2                  54      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt5                  54      // uint8_t
#define LOG_fOOnDpt5001               54      // uint8_t
#define LOG_fOOnDpt6                  54      // int8_t
#define LOG_fOOnDpt7                  54      // uint16_t
#define LOG_fOOnDpt8                  54      // int16_t
#define LOG_fOOnDpt9                  54      // float
#define LOG_fOOnDpt16                 54      // char*, 14 Byte
#define LOG_fOOnDpt17                 54      // 8 Bits, Bit 7-0
#define LOG_fOOnRGB                   54      // color, uint, 3 Byte
#define LOG_fOOnPAArea                54      // 4 Bits, Bit 7-4
#define     LOG_fOOnPAAreaMask 0xF0
#define     LOG_fOOnPAAreaShift 4
#define LOG_fOOnPALine                54      // 4 Bits, Bit 3-0
#define     LOG_fOOnPALineMask 0x0F
#define     LOG_fOOnPALineShift 0
#define LOG_fOOnPADevice              55      // uint8_t
#define LOG_fOOnFunction              54      // 8 Bits, Bit 7-0
#define LOG_fOOff                     68      // 8 Bits, Bit 7-0
#define LOG_fOOffBuzzer               68      // 8 Bits, Bit 7-0
#define LOG_fOOffLed                  68      // 8 Bits, Bit 7-0
#define LOG_fOOffAll                  68      // 8 Bits, Bit 7-0
#define LOG_fOOffTone                 69      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt1                 69      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt2                 69      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt5                 69      // uint8_t
#define LOG_fOOffDpt5001              69      // uint8_t
#define LOG_fOOffDpt6                 69      // int8_t
#define LOG_fOOffDpt7                 69      // uint16_t
#define LOG_fOOffDpt8                 69      // int16_t
#define LOG_fOOffDpt9                 69      // float
#define LOG_fOOffDpt16                69      // char*, 14 Byte
#define LOG_fOOffDpt17                69      // 8 Bits, Bit 7-0
#define LOG_fOOffRGB                  69      // color, uint, 3 Byte
#define LOG_fOOffPAArea               69      // 4 Bits, Bit 7-4
#define     LOG_fOOffPAAreaMask 0xF0
#define     LOG_fOOffPAAreaShift 4
#define LOG_fOOffPALine               69      // 4 Bits, Bit 3-0
#define     LOG_fOOffPALineMask 0x0F
#define     LOG_fOOffPALineShift 0
#define LOG_fOOffPADevice             70      // uint8_t
#define LOG_fOOffFunction             69      // 8 Bits, Bit 7-0
#define LOG_fE1UseOtherKO             83      // 1 Bit, Bit 7
#define     LOG_fE1UseOtherKOMask 0x80
#define     LOG_fE1UseOtherKOShift 7
#define LOG_fE1OtherKO                83      // uint12_t
#define LOG_fE2UseOtherKO             85      // 1 Bit, Bit 7
#define     LOG_fE2UseOtherKOMask 0x80
#define     LOG_fE2UseOtherKOShift 7
#define LOG_fE2OtherKO                85      // uint12_t

// Communication objects per channel (multiple occurance)
#define LOG_KoOffset 450
#define LOG_KoBlockSize 3
#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

#define PM_ChannelCount 20

// Parameter per channel
#define PM_ParamBlockOffset 2658
#define PM_ParamBlockSize 94
#define PM_pPresence1Type             0      // 2 Bits, Bit 7-6
#define     PM_pPresence1TypeMask 0xC0
#define     PM_pPresence1TypeShift 6
#define PM_pPresence2Type             0      // 2 Bits, Bit 5-4
#define     PM_pPresence2TypeMask 0x30
#define     PM_pPresence2TypeShift 4
#define PM_pPresenceIntern            0      // 1 Bit, Bit 3
#define     PM_pPresenceInternMask 0x08
#define     PM_pPresenceInternShift 3
#define PM_pPhaseBool                 0      // 1 Bit, Bit 2
#define     PM_pPhaseBoolMask 0x04
#define     PM_pPhaseBoolShift 2
#define PM_pPhaseCount                0      // 2 Bits, Bit 1-0
#define     PM_pPhaseCountMask 0x03
#define     PM_pPhaseCountShift 0
#define PM_pOutput1Type               1      // 3 Bits, Bit 7-5
#define     PM_pOutput1TypeMask 0xE0
#define     PM_pOutput1TypeShift 5
#define PM_pOutput2Type               1      // 3 Bits, Bit 4-2
#define     PM_pOutput2TypeMask 0x1C
#define     PM_pOutput2TypeShift 2
#define PM_pChannelActive             1      // 2 Bits, Bit 1-0
#define     PM_pChannelActiveMask 0x03
#define     PM_pChannelActiveShift 0
#define PM_pBrightnessIndependent     2      // 1 Bit, Bit 7
#define     PM_pBrightnessIndependentMask 0x80
#define     PM_pBrightnessIndependentShift 7
#define PM_pOutput1Cyclic             2      // 1 Bit, Bit 6
#define     PM_pOutput1CyclicMask 0x40
#define     PM_pOutput1CyclicShift 6
#define PM_pOutput2Cyclic             2      // 1 Bit, Bit 5
#define     PM_pOutput2CyclicMask 0x20
#define     PM_pOutput2CyclicShift 5
#define PM_pLockType                  2      // 2 Bits, Bit 4-3
#define     PM_pLockTypeMask 0x18
#define     PM_pLockTypeShift 3
#define PM_pLockActive                2      // 1 Bit, Bit 2
#define     PM_pLockActiveMask 0x04
#define     PM_pLockActiveShift 2
#define PM_pLockOn                    2      // 2 Bits, Bit 1-0
#define     PM_pLockOnMask 0x03
#define     PM_pLockOnShift 0
#define PM_pLockOff                   3      // 2 Bits, Bit 7-6
#define     PM_pLockOffMask 0xC0
#define     PM_pLockOffShift 6
#define PM_pLockFallback              3      // 1 Bit, Bit 5
#define     PM_pLockFallbackMask 0x20
#define     PM_pLockFallbackShift 5
#define PM_pPhaseChange               3      // 1 Bit, Bit 4
#define     PM_pPhaseChangeMask 0x10
#define     PM_pPhaseChangeShift 4
#define PM_pChannelDelayBase          4      // 2 Bits, Bit 7-6
#define     PM_pChannelDelayBaseMask 0xC0
#define     PM_pChannelDelayBaseShift 6
#define PM_pChannelDelayTime          4      // uint14_t
#define PM_pOutput1CyclicBase         6      // 2 Bits, Bit 7-6
#define     PM_pOutput1CyclicBaseMask 0xC0
#define     PM_pOutput1CyclicBaseShift 6
#define PM_pOutput1CyclicTime         6      // uint14_t
#define PM_pOutput2CyclicBase         8      // 2 Bits, Bit 7-6
#define     PM_pOutput2CyclicBaseMask 0xC0
#define     PM_pOutput2CyclicBaseShift 6
#define PM_pOutput2CyclicTime         8      // uint14_t
#define PM_pLockFallbackBase         10      // 2 Bits, Bit 7-6
#define     PM_pLockFallbackBaseMask 0xC0
#define     PM_pLockFallbackBaseShift 6
#define PM_pLockFallbackTime          8      // uint14_t
#define PM_pPhase1Scene              10      // 8 Bits, Bit 7-0
#define PM_pPhase2Scene              11      // 8 Bits, Bit 7-0
#define PM_pPhase3Scene              12      // 8 Bits, Bit 7-0
#define PM_pPhase4Scene              13      // 8 Bits, Bit 7-0
#define PM_pABrightnessAuto          14      // 2 Bits, Bit 7-6
#define     PM_pABrightnessAutoMask 0xC0
#define     PM_pABrightnessAutoShift 6
#define PM_pAPresenceShort           14      // 1 Bit, Bit 5
#define     PM_pAPresenceShortMask 0x20
#define     PM_pAPresenceShortShift 5
#define PM_pAOutput1Send             14      // 1 Bit, Bit 4
#define     PM_pAOutput1SendMask 0x10
#define     PM_pAOutput1SendShift 4
#define PM_pAOutput2Send             14      // 1 Bit, Bit 3
#define     PM_pAOutput2SendMask 0x08
#define     PM_pAOutput2SendShift 3
#define PM_pABrightnessRead          14      // 1 Bit, Bit 2
#define     PM_pABrightnessReadMask 0x04
#define     PM_pABrightnessReadShift 2
#define PM_pAOutput1Filter           14      // 2 Bits, Bit 1-0
#define     PM_pAOutput1FilterMask 0x03
#define     PM_pAOutput1FilterShift 0
#define PM_pAOutput2Filter           15      // 2 Bits, Bit 7-6
#define     PM_pAOutput2FilterMask 0xC0
#define     PM_pAOutput2FilterShift 6
#define PM_pAPresenceDelayBase       16      // 2 Bits, Bit 7-6
#define     PM_pAPresenceDelayBaseMask 0xC0
#define     PM_pAPresenceDelayBaseShift 6
#define PM_pAPresenceDelayTime       16      // uint14_t
#define PM_pAPresenceShortDurationBase 18      // 2 Bits, Bit 7-6
#define     PM_pAPresenceShortDurationBaseMask 0xC0
#define     PM_pAPresenceShortDurationBaseShift 6
#define PM_pAPresenceShortDurationTime 18      // uint14_t
#define PM_pAPresenceShortDelayBase  20      // 2 Bits, Bit 7-6
#define     PM_pAPresenceShortDelayBaseMask 0xC0
#define     PM_pAPresenceShortDelayBaseShift 6
#define PM_pAPresenceShortDelayTime  20      // uint14_t
#define PM_pABrightnessAdaptiveDelayBase 22      // 2 Bits, Bit 7-6
#define     PM_pABrightnessAdaptiveDelayBaseMask 0xC0
#define     PM_pABrightnessAdaptiveDelayBaseShift 6
#define PM_pABrightnessAdaptiveDelayTime 22      // uint14_t
#define PM_pABrightnessOn            24      // uint16_t
#define PM_pABrightnessDelta         26      // uint16_t
#define PM_pAOutput1On               28      // 8 Bits, Bit 7-0
#define PM_pAOutput1OnValue          28      // uint8_t
#define PM_pAOutput1OnScene          28      // 8 Bits, Bit 7-0
#define PM_pAOutput1OnDim            28      // uint8_t
#define PM_pAOutput1Off              29      // 8 Bits, Bit 7-0
#define PM_pAOutput1OffValue         29      // uint8_t
#define PM_pAOutput1OffScene         29      // 8 Bits, Bit 7-0
#define PM_pAOutput1OffDim           29      // uint8_t
#define PM_pAOutput2On               30      // 8 Bits, Bit 7-0
#define PM_pAOutput2OnValue          30      // uint8_t
#define PM_pAOutput2OnScene          30      // 8 Bits, Bit 7-0
#define PM_pAOutput2OnDim            30      // uint8_t
#define PM_pAOutput2Off              31      // 8 Bits, Bit 7-0
#define PM_pAOutput2OffValue         31      // uint8_t
#define PM_pAOutput2OffScene         31      // 8 Bits, Bit 7-0
#define PM_pAOutput2OffDim           31      // uint8_t
#define PM_pAManualFallbackDelayBase 32      // 2 Bits, Bit 7-6
#define     PM_pAManualFallbackDelayBaseMask 0xC0
#define     PM_pAManualFallbackDelayBaseShift 6
#define PM_pAManualFallbackDelayTime 32      // uint14_t
#define PM_pBBrightnessAuto          34      // 2 Bits, Bit 7-6
#define     PM_pBBrightnessAutoMask 0xC0
#define     PM_pBBrightnessAutoShift 6
#define PM_pBPresenceShort           34      // 1 Bit, Bit 5
#define     PM_pBPresenceShortMask 0x20
#define     PM_pBPresenceShortShift 5
#define PM_pBOutput1Send             34      // 1 Bit, Bit 4
#define     PM_pBOutput1SendMask 0x10
#define     PM_pBOutput1SendShift 4
#define PM_pBOutput2Send             34      // 1 Bit, Bit 3
#define     PM_pBOutput2SendMask 0x08
#define     PM_pBOutput2SendShift 3
#define PM_pBBrightnessRead          34      // 1 Bit, Bit 2
#define     PM_pBBrightnessReadMask 0x04
#define     PM_pBBrightnessReadShift 2
#define PM_pBOutput1Filter           34      // 2 Bits, Bit 1-0
#define     PM_pBOutput1FilterMask 0x03
#define     PM_pBOutput1FilterShift 0
#define PM_pBOutput2Filter           35      // 2 Bits, Bit 7-6
#define     PM_pBOutput2FilterMask 0xC0
#define     PM_pBOutput2FilterShift 6
#define PM_pBPresenceDelayBase       36      // 2 Bits, Bit 7-6
#define     PM_pBPresenceDelayBaseMask 0xC0
#define     PM_pBPresenceDelayBaseShift 6
#define PM_pBPresenceDelayTime       36      // uint14_t
#define PM_pBPresenceShortDurationBase 38      // 2 Bits, Bit 7-6
#define     PM_pBPresenceShortDurationBaseMask 0xC0
#define     PM_pBPresenceShortDurationBaseShift 6
#define PM_pBPresenceShortDurationTime 38      // uint14_t
#define PM_pBPresenceShortDelayBase  40      // 2 Bits, Bit 7-6
#define     PM_pBPresenceShortDelayBaseMask 0xC0
#define     PM_pBPresenceShortDelayBaseShift 6
#define PM_pBPresenceShortDelayTime  40      // uint14_t
#define PM_pBBrightnessAdaptiveDelayBase 42      // 2 Bits, Bit 7-6
#define     PM_pBBrightnessAdaptiveDelayBaseMask 0xC0
#define     PM_pBBrightnessAdaptiveDelayBaseShift 6
#define PM_pBBrightnessAdaptiveDelayTime 42      // uint14_t
#define PM_pBBrightnessOn            44      // uint16_t
#define PM_pBBrightnessDelta         46      // uint16_t
#define PM_pBOutput1On               48      // 8 Bits, Bit 7-0
#define PM_pBOutput1OnValue          48      // uint8_t
#define PM_pBOutput1OnScene          48      // 8 Bits, Bit 7-0
#define PM_pBOutput1OnDim            48      // uint8_t
#define PM_pBOutput1Off              49      // 8 Bits, Bit 7-0
#define PM_pBOutput1OffValue         49      // uint8_t
#define PM_pBOutput1OffScene         49      // 8 Bits, Bit 7-0
#define PM_pBOutput1OffDim           49      // uint8_t
#define PM_pBOutput2On               50      // 8 Bits, Bit 7-0
#define PM_pBOutput2OnValue          50      // uint8_t
#define PM_pBOutput2OnScene          50      // 8 Bits, Bit 7-0
#define PM_pBOutput2OnDim            50      // uint8_t
#define PM_pBOutput2Off              51      // 8 Bits, Bit 7-0
#define PM_pBOutput2OffValue         51      // uint8_t
#define PM_pBOutput2OffScene         51      // 8 Bits, Bit 7-0
#define PM_pBOutput2OffDim           51      // uint8_t
#define PM_pBManualFallbackDelayBase 52      // 2 Bits, Bit 7-6
#define     PM_pBManualFallbackDelayBaseMask 0xC0
#define     PM_pBManualFallbackDelayBaseShift 6
#define PM_pBManualFallbackDelayTime 52      // uint14_t
#define PM_pCBrightnessAuto          54      // 2 Bits, Bit 7-6
#define     PM_pCBrightnessAutoMask 0xC0
#define     PM_pCBrightnessAutoShift 6
#define PM_pCPresenceShort           54      // 1 Bit, Bit 5
#define     PM_pCPresenceShortMask 0x20
#define     PM_pCPresenceShortShift 5
#define PM_pCOutput1Send             54      // 1 Bit, Bit 4
#define     PM_pCOutput1SendMask 0x10
#define     PM_pCOutput1SendShift 4
#define PM_pCOutput2Send             54      // 1 Bit, Bit 3
#define     PM_pCOutput2SendMask 0x08
#define     PM_pCOutput2SendShift 3
#define PM_pCBrightnessRead          54      // 1 Bit, Bit 2
#define     PM_pCBrightnessReadMask 0x04
#define     PM_pCBrightnessReadShift 2
#define PM_pCOutput1Filter           54      // 2 Bits, Bit 1-0
#define     PM_pCOutput1FilterMask 0x03
#define     PM_pCOutput1FilterShift 0
#define PM_pCOutput2Filter           55      // 2 Bits, Bit 7-6
#define     PM_pCOutput2FilterMask 0xC0
#define     PM_pCOutput2FilterShift 6
#define PM_pCPresenceDelayBase       56      // 2 Bits, Bit 7-6
#define     PM_pCPresenceDelayBaseMask 0xC0
#define     PM_pCPresenceDelayBaseShift 6
#define PM_pCPresenceDelayTime       56      // uint14_t
#define PM_pCPresenceShortDurationBase 58      // 2 Bits, Bit 7-6
#define     PM_pCPresenceShortDurationBaseMask 0xC0
#define     PM_pCPresenceShortDurationBaseShift 6
#define PM_pCPresenceShortDurationTime 58      // uint14_t
#define PM_pCPresenceShortDelayBase  60      // 2 Bits, Bit 7-6
#define     PM_pCPresenceShortDelayBaseMask 0xC0
#define     PM_pCPresenceShortDelayBaseShift 6
#define PM_pCPresenceShortDelayTime  60      // uint14_t
#define PM_pCBrightnessAdaptiveDelayBase 62      // 2 Bits, Bit 7-6
#define     PM_pCBrightnessAdaptiveDelayBaseMask 0xC0
#define     PM_pCBrightnessAdaptiveDelayBaseShift 6
#define PM_pCBrightnessAdaptiveDelayTime 62      // uint14_t
#define PM_pCBrightnessOn            64      // uint16_t
#define PM_pCBrightnessDelta         66      // uint16_t
#define PM_pCOutput1On               68      // 8 Bits, Bit 7-0
#define PM_pCOutput1OnValue          68      // uint8_t
#define PM_pCOutput1OnScene          68      // 8 Bits, Bit 7-0
#define PM_pCOutput1OnDim            68      // uint8_t
#define PM_pCOutput1Off              69      // 8 Bits, Bit 7-0
#define PM_pCOutput1OffValue         69      // uint8_t
#define PM_pCOutput1OffScene         69      // 8 Bits, Bit 7-0
#define PM_pCOutput1OffDim           69      // uint8_t
#define PM_pCOutput2On               70      // 8 Bits, Bit 7-0
#define PM_pCOutput2OnValue          70      // uint8_t
#define PM_pCOutput2OnScene          70      // 8 Bits, Bit 7-0
#define PM_pCOutput2OnDim            70      // uint8_t
#define PM_pCOutput2Off              71      // 8 Bits, Bit 7-0
#define PM_pCOutput2OffValue         71      // uint8_t
#define PM_pCOutput2OffScene         71      // 8 Bits, Bit 7-0
#define PM_pCOutput2OffDim           71      // uint8_t
#define PM_pCManualFallbackDelayBase 72      // 2 Bits, Bit 7-6
#define     PM_pCManualFallbackDelayBaseMask 0xC0
#define     PM_pCManualFallbackDelayBaseShift 6
#define PM_pCManualFallbackDelayTime 72      // uint14_t
#define PM_pDBrightnessAuto          74      // 2 Bits, Bit 7-6
#define     PM_pDBrightnessAutoMask 0xC0
#define     PM_pDBrightnessAutoShift 6
#define PM_pDPresenceShort           74      // 1 Bit, Bit 5
#define     PM_pDPresenceShortMask 0x20
#define     PM_pDPresenceShortShift 5
#define PM_pDOutput1Send             74      // 1 Bit, Bit 4
#define     PM_pDOutput1SendMask 0x10
#define     PM_pDOutput1SendShift 4
#define PM_pDOutput2Send             74      // 1 Bit, Bit 3
#define     PM_pDOutput2SendMask 0x08
#define     PM_pDOutput2SendShift 3
#define PM_pDBrightnessRead          74      // 1 Bit, Bit 2
#define     PM_pDBrightnessReadMask 0x04
#define     PM_pDBrightnessReadShift 2
#define PM_pDOutput1Filter           74      // 2 Bits, Bit 1-0
#define     PM_pDOutput1FilterMask 0x03
#define     PM_pDOutput1FilterShift 0
#define PM_pDOutput2Filter           75      // 2 Bits, Bit 7-6
#define     PM_pDOutput2FilterMask 0xC0
#define     PM_pDOutput2FilterShift 6
#define PM_pDPresenceDelayBase       76      // 2 Bits, Bit 7-6
#define     PM_pDPresenceDelayBaseMask 0xC0
#define     PM_pDPresenceDelayBaseShift 6
#define PM_pDPresenceDelayTime       76      // uint14_t
#define PM_pDPresenceShortDurationBase 78      // 2 Bits, Bit 7-6
#define     PM_pDPresenceShortDurationBaseMask 0xC0
#define     PM_pDPresenceShortDurationBaseShift 6
#define PM_pDPresenceShortDurationTime 78      // uint14_t
#define PM_pDPresenceShortDelayBase  80      // 2 Bits, Bit 7-6
#define     PM_pDPresenceShortDelayBaseMask 0xC0
#define     PM_pDPresenceShortDelayBaseShift 6
#define PM_pDPresenceShortDelayTime  80      // uint14_t
#define PM_pDBrightnessAdaptiveDelayBase 82      // 2 Bits, Bit 7-6
#define     PM_pDBrightnessAdaptiveDelayBaseMask 0xC0
#define     PM_pDBrightnessAdaptiveDelayBaseShift 6
#define PM_pDBrightnessAdaptiveDelayTime 82      // uint14_t
#define PM_pDBrightnessOn            84      // uint16_t
#define PM_pDBrightnessDelta         86      // uint16_t
#define PM_pDOutput1On               88      // 8 Bits, Bit 7-0
#define PM_pDOutput1OnValue          88      // uint8_t
#define PM_pDOutput1OnScene          88      // 8 Bits, Bit 7-0
#define PM_pDOutput1OnDim            88      // uint8_t
#define PM_pDOutput1Off              89      // 8 Bits, Bit 7-0
#define PM_pDOutput1OffValue         89      // uint8_t
#define PM_pDOutput1OffScene         89      // 8 Bits, Bit 7-0
#define PM_pDOutput1OffDim           89      // uint8_t
#define PM_pDOutput2On               90      // 8 Bits, Bit 7-0
#define PM_pDOutput2OnValue          90      // uint8_t
#define PM_pDOutput2OnScene          90      // 8 Bits, Bit 7-0
#define PM_pDOutput2OnDim            90      // uint8_t
#define PM_pDOutput2Off              91      // 8 Bits, Bit 7-0
#define PM_pDOutput2OffValue         91      // uint8_t
#define PM_pDOutput2OffScene         91      // 8 Bits, Bit 7-0
#define PM_pDOutput2OffDim           91      // uint8_t
#define PM_pDManualFallbackDelayBase 92      // 2 Bits, Bit 7-6
#define     PM_pDManualFallbackDelayBaseMask 0xC0
#define     PM_pDManualFallbackDelayBaseShift 6
#define PM_pDManualFallbackDelayTime 92      // uint14_t

// Communication objects per channel (multiple occurance)
#define PM_KoOffset 50
#define PM_KoBlockSize 20
#define PM_KoKOpLux 0
#define PM_KoKOpPresence1 1
#define PM_KoKOpPresence2 2
#define PM_KoKOpSetAutomatic 3
#define PM_KoKOpSetManual 4
#define PM_KoKOpAktorState 5
#define PM_KoKOpRecalcLuxOff 6
#define PM_KoKOpLock 7
#define PM_KoKOpReset 8
#define PM_KoKOpDayPhase 9
#define PM_KoKOpLuxOn 10
#define PM_KoKOpPresenceDelay 11
#define PM_KoKOpSceneCommand 12
#define PM_KoKOpOutput 13
#define PM_KoKOpOutput2 14
#define PM_KoKOpIsManual 15
#define PM_KoKOpManualDimRel 16
#define PM_KoKOpManualDimAbs 17
#define PM_KoKOpManualDimScene 18
#define PM_KoKOpReserve 19

#define MAIN_OpenKnxId 0xA0
#define MAIN_ApplicationNumber 1
#define MAIN_ApplicationVersion 15
