#pragma once

// Parameter with single occurrence

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
#define LOG_Frauentag                  7      // 1 Bit, Bit 1
#define     LOG_FrauentagMask 0x02
#define     LOG_FrauentagShift 1
#define LOG_Gruendonnerstag            7      // 1 Bit, Bit 0
#define     LOG_GruendonnerstagMask 0x01
#define     LOG_GruendonnerstagShift 0
#define LOG_Karfreitag                 8      // 1 Bit, Bit 7
#define     LOG_KarfreitagMask 0x80
#define     LOG_KarfreitagShift 7
#define LOG_Ostersonntag               8      // 1 Bit, Bit 6
#define     LOG_OstersonntagMask 0x40
#define     LOG_OstersonntagShift 6
#define LOG_Ostermontag                8      // 1 Bit, Bit 5
#define     LOG_OstermontagMask 0x20
#define     LOG_OstermontagShift 5
#define LOG_TagDerArbeit               8      // 1 Bit, Bit 4
#define     LOG_TagDerArbeitMask 0x10
#define     LOG_TagDerArbeitShift 4
#define LOG_Himmelfahrt                8      // 1 Bit, Bit 3
#define     LOG_HimmelfahrtMask 0x08
#define     LOG_HimmelfahrtShift 3
#define LOG_Pfingstsonntag             8      // 1 Bit, Bit 2
#define     LOG_PfingstsonntagMask 0x04
#define     LOG_PfingstsonntagShift 2
#define LOG_Pfingstmontag              8      // 1 Bit, Bit 1
#define     LOG_PfingstmontagMask 0x02
#define     LOG_PfingstmontagShift 1
#define LOG_Fronleichnam               8      // 1 Bit, Bit 0
#define     LOG_FronleichnamMask 0x01
#define     LOG_FronleichnamShift 0
#define LOG_Friedensfest               9      // 1 Bit, Bit 7
#define     LOG_FriedensfestMask 0x80
#define     LOG_FriedensfestShift 7
#define LOG_MariaHimmelfahrt           9      // 1 Bit, Bit 6
#define     LOG_MariaHimmelfahrtMask 0x40
#define     LOG_MariaHimmelfahrtShift 6
#define LOG_DeutscheEinheit            9      // 1 Bit, Bit 5
#define     LOG_DeutscheEinheitMask 0x20
#define     LOG_DeutscheEinheitShift 5
#define LOG_Reformationstag            9      // 1 Bit, Bit 4
#define     LOG_ReformationstagMask 0x10
#define     LOG_ReformationstagShift 4
#define LOG_Allerheiligen              9      // 1 Bit, Bit 3
#define     LOG_AllerheiligenMask 0x08
#define     LOG_AllerheiligenShift 3
#define LOG_BussBettag                 9      // 1 Bit, Bit 2
#define     LOG_BussBettagMask 0x04
#define     LOG_BussBettagShift 2
#define LOG_Advent1                    9      // 1 Bit, Bit 1
#define     LOG_Advent1Mask 0x02
#define     LOG_Advent1Shift 1
#define LOG_Advent2                    9      // 1 Bit, Bit 0
#define     LOG_Advent2Mask 0x01
#define     LOG_Advent2Shift 0
#define LOG_Advent3                   10      // 1 Bit, Bit 7
#define     LOG_Advent3Mask 0x80
#define     LOG_Advent3Shift 7
#define LOG_Advent4                   10      // 1 Bit, Bit 6
#define     LOG_Advent4Mask 0x40
#define     LOG_Advent4Shift 6
#define LOG_Heiligabend               10      // 1 Bit, Bit 5
#define     LOG_HeiligabendMask 0x20
#define     LOG_HeiligabendShift 5
#define LOG_Weihnachtstag1            10      // 1 Bit, Bit 4
#define     LOG_Weihnachtstag1Mask 0x10
#define     LOG_Weihnachtstag1Shift 4
#define LOG_Weihnachtstag2            10      // 1 Bit, Bit 3
#define     LOG_Weihnachtstag2Mask 0x08
#define     LOG_Weihnachtstag2Shift 3
#define LOG_Silvester                 10      // 1 Bit, Bit 2
#define     LOG_SilvesterMask 0x04
#define     LOG_SilvesterShift 2
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
#define PM_SendRAW                   41      // 1 Bit, Bit 7
#define     PM_SendRAWMask 0x80
#define     PM_SendRAWShift 7
#define PM_LEDPresence               41      // 2 Bits, Bit 6-5
#define     PM_LEDPresenceMask 0x60
#define     PM_LEDPresenceShift 5
#define PM_LEDMove                   41      // 2 Bits, Bit 4-3
#define     PM_LEDMoveMask 0x18
#define     PM_LEDMoveShift 3
#define PM_HWPresence                41      // 3 Bits, Bit 2-0
#define     PM_HWPresenceMask 0x07
#define     PM_HWPresenceShift 0
#define PM_HWLux                     42      // 2 Bits, Bit 7-6
#define     PM_HWLuxMask 0xC0
#define     PM_HWLuxShift 6
#define PM_ReadLed                   42      // 1 Bit, Bit 5
#define     PM_ReadLedMask 0x20
#define     PM_ReadLedShift 5
#define PM_LuxOffsetPM               43      // int8_t
#define PM_LuxSendDeltaAbsRel        44      // 1 Bit, Bit 7
#define     PM_LuxSendDeltaAbsRelMask 0x80
#define     PM_LuxSendDeltaAbsRelShift 7
#define PM_LuxSendDelta              44      // uint15_t
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
#define LOG_ParamBlockSize 86
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
#define LOG_fTGate                     3      // 1 Bit, Bit 4
#define     LOG_fTGateMask 0x10
#define     LOG_fTGateShift 4
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
#define LOG_fTriggerGateClose          5      // 2 Bits, Bit 7-6
#define     LOG_fTriggerGateCloseMask 0xC0
#define     LOG_fTriggerGateCloseShift 6
#define LOG_fTriggerGateOpen           5      // 2 Bits, Bit 5-4
#define     LOG_fTriggerGateOpenMask 0x30
#define     LOG_fTriggerGateOpenShift 4
#define LOG_fE1                        6      // 4 Bits, Bit 3-0
#define     LOG_fE1Mask 0x0F
#define     LOG_fE1Shift 0
#define LOG_fE1Convert                 6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertMask 0xF0
#define     LOG_fE1ConvertShift 4
#define LOG_fE1ConvertFloat            6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertFloatMask 0xF0
#define     LOG_fE1ConvertFloatShift 4
#define LOG_fE1ConvertSpecial          6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertSpecialMask 0xF0
#define     LOG_fE1ConvertSpecialShift 4
#define LOG_fE1Dpt                     7      // 8 Bits, Bit 7-0
#define LOG_fE1Default                 8      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultMask 0x03
#define     LOG_fE1DefaultShift 0
#define LOG_fE1DefaultExt              8      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultExtMask 0x03
#define     LOG_fE1DefaultExtShift 0
#define LOG_fE1DefaultEEPROM           8      // 1 Bit, Bit 2
#define     LOG_fE1DefaultEEPROMMask 0x04
#define     LOG_fE1DefaultEEPROMShift 2
#define LOG_fE1DefaultRepeat           8      // 1 Bit, Bit 3
#define     LOG_fE1DefaultRepeatMask 0x08
#define     LOG_fE1DefaultRepeatShift 3
#define LOG_fTYearDay                  8      // 1 Bit, Bit 4
#define     LOG_fTYearDayMask 0x10
#define     LOG_fTYearDayShift 4
#define LOG_fTRestoreState             8      // 2 Bits, Bit 6-5
#define     LOG_fTRestoreStateMask 0x60
#define     LOG_fTRestoreStateShift 5
#define LOG_fE1RepeatBase              9      // 2 Bits, Bit 7-6
#define     LOG_fE1RepeatBaseMask 0xC0
#define     LOG_fE1RepeatBaseShift 6
#define LOG_fE1RepeatTime              9      // uint14_t
#define LOG_fE2                       11      // 4 Bits, Bit 3-0
#define     LOG_fE2Mask 0x0F
#define     LOG_fE2Shift 0
#define LOG_fE2Convert                11      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertMask 0xF0
#define     LOG_fE2ConvertShift 4
#define LOG_fE2ConvertFloat           11      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertFloatMask 0xF0
#define     LOG_fE2ConvertFloatShift 4
#define LOG_fE2ConvertSpecial         11      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertSpecialMask 0xF0
#define     LOG_fE2ConvertSpecialShift 4
#define LOG_fE2Dpt                    12      // 8 Bits, Bit 7-0
#define LOG_fE2Default                13      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultMask 0x03
#define     LOG_fE2DefaultShift 0
#define LOG_fE2DefaultExt             13      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultExtMask 0x03
#define     LOG_fE2DefaultExtShift 0
#define LOG_fE2DefaultEEPROM          13      // 1 Bit, Bit 2
#define     LOG_fE2DefaultEEPROMMask 0x04
#define     LOG_fE2DefaultEEPROMShift 2
#define LOG_fE2DefaultRepeat          13      // 1 Bit, Bit 3
#define     LOG_fE2DefaultRepeatMask 0x08
#define     LOG_fE2DefaultRepeatShift 3
#define LOG_fTHoliday                 13      // 2 Bits, Bit 4-3
#define     LOG_fTHolidayMask 0x18
#define     LOG_fTHolidayShift 3
#define LOG_fTVacation                13      // 2 Bits, Bit 6-5
#define     LOG_fTVacationMask 0x60
#define     LOG_fTVacationShift 5
#define LOG_fE2RepeatBase             14      // 2 Bits, Bit 7-6
#define     LOG_fE2RepeatBaseMask 0xC0
#define     LOG_fE2RepeatBaseShift 6
#define LOG_fE2RepeatTime             14      // uint14_t
#define LOG_fTd1DuskDawn              14      // 4 Bits, Bit 7-4
#define     LOG_fTd1DuskDawnMask 0xF0
#define     LOG_fTd1DuskDawnShift 4
#define LOG_fTd2DuskDawn              14      // 4 Bits, Bit 3-0
#define     LOG_fTd2DuskDawnMask 0x0F
#define     LOG_fTd2DuskDawnShift 0
#define LOG_fTd3DuskDawn              15      // 4 Bits, Bit 7-4
#define     LOG_fTd3DuskDawnMask 0xF0
#define     LOG_fTd3DuskDawnShift 4
#define LOG_fTd4DuskDawn              15      // 4 Bits, Bit 3-0
#define     LOG_fTd4DuskDawnMask 0x0F
#define     LOG_fTd4DuskDawnShift 0
#define LOG_fTd5DuskDawn              16      // 4 Bits, Bit 7-4
#define     LOG_fTd5DuskDawnMask 0xF0
#define     LOG_fTd5DuskDawnShift 4
#define LOG_fTd6DuskDawn              16      // 4 Bits, Bit 3-0
#define     LOG_fTd6DuskDawnMask 0x0F
#define     LOG_fTd6DuskDawnShift 0
#define LOG_fTd7DuskDawn              17      // 4 Bits, Bit 7-4
#define     LOG_fTd7DuskDawnMask 0xF0
#define     LOG_fTd7DuskDawnShift 4
#define LOG_fTd8DuskDawn              17      // 4 Bits, Bit 3-0
#define     LOG_fTd8DuskDawnMask 0x0F
#define     LOG_fTd8DuskDawnShift 0
#define LOG_fE1LowDelta               18      // int32_t
#define LOG_fE1HighDelta              22      // int32_t
#define LOG_fE1LowDeltaFloat          18      // float
#define LOG_fE1HighDeltaFloat         22      // float
#define LOG_fE1Low0Valid              25      // 1 Bit, Bit 7
#define     LOG_fE1Low0ValidMask 0x80
#define     LOG_fE1Low0ValidShift 7
#define LOG_fE1Low1Valid              25      // 1 Bit, Bit 6
#define     LOG_fE1Low1ValidMask 0x40
#define     LOG_fE1Low1ValidShift 6
#define LOG_fE1Low2Valid              25      // 1 Bit, Bit 5
#define     LOG_fE1Low2ValidMask 0x20
#define     LOG_fE1Low2ValidShift 5
#define LOG_fE1Low3Valid              25      // 1 Bit, Bit 4
#define     LOG_fE1Low3ValidMask 0x10
#define     LOG_fE1Low3ValidShift 4
#define LOG_fE1Low4Valid              25      // 1 Bit, Bit 3
#define     LOG_fE1Low4ValidMask 0x08
#define     LOG_fE1Low4ValidShift 3
#define LOG_fE1Low5Valid              25      // 1 Bit, Bit 2
#define     LOG_fE1Low5ValidMask 0x04
#define     LOG_fE1Low5ValidShift 2
#define LOG_fE1Low6Valid              25      // 1 Bit, Bit 1
#define     LOG_fE1Low6ValidMask 0x02
#define     LOG_fE1Low6ValidShift 1
#define LOG_fE1Low7Valid              25      // 1 Bit, Bit 0
#define     LOG_fE1Low7ValidMask 0x01
#define     LOG_fE1Low7ValidShift 0
#define LOG_fE1LowDpt2                18      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt2               19      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt2               20      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt2               21      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt2Fix             18      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt5                18      // uint8_t
#define LOG_fE1HighDpt5               22      // uint8_t
#define LOG_fE1Low0Dpt5In             18      // uint8_t
#define LOG_fE1Low1Dpt5In             19      // uint8_t
#define LOG_fE1Low2Dpt5In             20      // uint8_t
#define LOG_fE1Low3Dpt5In             21      // uint8_t
#define LOG_fE1Low4Dpt5In             22      // uint8_t
#define LOG_fE1Low5Dpt5In             23      // uint8_t
#define LOG_fE1Low6Dpt5In             24      // uint8_t
#define LOG_fE1LowDpt5Fix             18      // uint8_t
#define LOG_fE1LowDpt5001             18      // uint8_t
#define LOG_fE1HighDpt5001            22      // uint8_t
#define LOG_fE1Low0Dpt5xIn            18      // uint8_t
#define LOG_fE1Low1Dpt5xIn            19      // uint8_t
#define LOG_fE1Low2Dpt5xIn            20      // uint8_t
#define LOG_fE1Low3Dpt5xIn            21      // uint8_t
#define LOG_fE1Low4Dpt5xIn            22      // uint8_t
#define LOG_fE1Low5Dpt5xIn            23      // uint8_t
#define LOG_fE1Low6Dpt5xIn            24      // uint8_t
#define LOG_fE1LowDpt5xFix            18      // uint8_t
#define LOG_fE1LowDpt6                18      // int8_t
#define LOG_fE1HighDpt6               22      // int8_t
#define LOG_fE1Low0Dpt6In             18      // int8_t
#define LOG_fE1Low1Dpt6In             19      // int8_t
#define LOG_fE1Low2Dpt6In             20      // int8_t
#define LOG_fE1Low3Dpt6In             21      // int8_t
#define LOG_fE1Low4Dpt6In             22      // int8_t
#define LOG_fE1Low5Dpt6In             23      // int8_t
#define LOG_fE1Low6Dpt6In             24      // int8_t
#define LOG_fE1LowDpt6Fix             18      // int8_t
#define LOG_fE1LowDpt7                18      // uint16_t
#define LOG_fE1HighDpt7               22      // uint16_t
#define LOG_fE1Low0Dpt7In             18      // uint16_t
#define LOG_fE1Low1Dpt7In             20      // uint16_t
#define LOG_fE1Low2Dpt7In             22      // uint16_t
#define LOG_fE1LowDpt7Fix             18      // uint16_t
#define LOG_fE1LowDpt8                18      // int16_t
#define LOG_fE1HighDpt8               22      // int16_t
#define LOG_fE1Low0Dpt8In             18      // int16_t
#define LOG_fE1Low1Dpt8In             20      // int16_t
#define LOG_fE1Low2Dpt8In             22      // int16_t
#define LOG_fE1LowDpt8Fix             18      // int16_t
#define LOG_fE1LowDpt9                18      // float
#define LOG_fE1HighDpt9               22      // float
#define LOG_fE1LowDpt9Fix             18      // float
#define LOG_fE1Low0Dpt17              18      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt17              19      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt17              20      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt17              21      // 8 Bits, Bit 7-0
#define LOG_fE1Low4Dpt17              22      // 8 Bits, Bit 7-0
#define LOG_fE1Low5Dpt17              23      // 8 Bits, Bit 7-0
#define LOG_fE1Low6Dpt17              24      // 8 Bits, Bit 7-0
#define LOG_fE1Low7Dpt17              25      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt17Fix            18      // 8 Bits, Bit 7-0
#define LOG_fE1LowDptRGB              18      // int32_t
#define LOG_fE1HighDptRGB             22      // int32_t
#define LOG_fE1LowDptRGBFix           18      // int32_t
#define LOG_fE2LowDelta               26      // int32_t
#define LOG_fE2HighDelta              30      // int32_t
#define LOG_fE2LowDeltaFloat          26      // float
#define LOG_fE2HighDeltaFloat         30      // float
#define LOG_fE2Low0Valid              33      // 1 Bit, Bit 7
#define     LOG_fE2Low0ValidMask 0x80
#define     LOG_fE2Low0ValidShift 7
#define LOG_fE2Low1Valid              33      // 1 Bit, Bit 6
#define     LOG_fE2Low1ValidMask 0x40
#define     LOG_fE2Low1ValidShift 6
#define LOG_fE2Low2Valid              33      // 1 Bit, Bit 5
#define     LOG_fE2Low2ValidMask 0x20
#define     LOG_fE2Low2ValidShift 5
#define LOG_fE2Low3Valid              33      // 1 Bit, Bit 4
#define     LOG_fE2Low3ValidMask 0x10
#define     LOG_fE2Low3ValidShift 4
#define LOG_fE2Low4Valid              33      // 1 Bit, Bit 3
#define     LOG_fE2Low4ValidMask 0x08
#define     LOG_fE2Low4ValidShift 3
#define LOG_fE2Low5Valid              33      // 1 Bit, Bit 2
#define     LOG_fE2Low5ValidMask 0x04
#define     LOG_fE2Low5ValidShift 2
#define LOG_fE2Low6Valid              33      // 1 Bit, Bit 1
#define     LOG_fE2Low6ValidMask 0x02
#define     LOG_fE2Low6ValidShift 1
#define LOG_fE2Low7Valid              33      // 1 Bit, Bit 0
#define     LOG_fE2Low7ValidMask 0x01
#define     LOG_fE2Low7ValidShift 0
#define LOG_fE2Low0Dpt2               26      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt2               27      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt2               28      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt2               29      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt2Fix             26      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt5                26      // uint8_t
#define LOG_fE2HighDpt5               30      // uint8_t
#define LOG_fE2Low0Dpt5In             26      // uint8_t
#define LOG_fE2Low1Dpt5In             27      // uint8_t
#define LOG_fE2Low2Dpt5In             28      // uint8_t
#define LOG_fE2Low3Dpt5In             29      // uint8_t
#define LOG_fE2Low4Dpt5In             30      // uint8_t
#define LOG_fE2Low5Dpt5In             31      // uint8_t
#define LOG_fE2Low6Dpt5In             32      // uint8_t
#define LOG_fE2LowDpt5Fix             26      // uint8_t
#define LOG_fE2LowDpt5001             26      // uint8_t
#define LOG_fE2HighDpt5001            30      // uint8_t
#define LOG_fE2Low0Dpt5xIn            26      // uint8_t
#define LOG_fE2Low1Dpt5xIn            27      // uint8_t
#define LOG_fE2Low2Dpt5xIn            28      // uint8_t
#define LOG_fE2Low3Dpt5xIn            29      // uint8_t
#define LOG_fE2Low4Dpt5xIn            30      // uint8_t
#define LOG_fE2Low5Dpt5xIn            31      // uint8_t
#define LOG_fE2Low6Dpt5xIn            32      // uint8_t
#define LOG_fE2LowDpt5xFix            26      // uint8_t
#define LOG_fE2LowDpt6                26      // int8_t
#define LOG_fE2HighDpt6               30      // int8_t
#define LOG_fE2Low0Dpt6In             26      // int8_t
#define LOG_fE2Low1Dpt6In             27      // int8_t
#define LOG_fE2Low2Dpt6In             28      // int8_t
#define LOG_fE2Low3Dpt6In             29      // int8_t
#define LOG_fE2Low4Dpt6In             30      // int8_t
#define LOG_fE2Low5Dpt6In             31      // int8_t
#define LOG_fE2Low6Dpt6In             32      // int8_t
#define LOG_fE2LowDpt6Fix             26      // int8_t
#define LOG_fE2LowDpt7                26      // uint16_t
#define LOG_fE2HighDpt7               30      // uint16_t
#define LOG_fE2Low0Dpt7In             26      // uint16_t
#define LOG_fE2Low1Dpt7In             28      // uint16_t
#define LOG_fE2Low2Dpt7In             30      // uint16_t
#define LOG_fE2LowDpt7Fix             26      // uint16_t
#define LOG_fE2LowDpt8                26      // int16_t
#define LOG_fE2HighDpt8               30      // int16_t
#define LOG_fE2Low0Dpt8In             26      // int16_t
#define LOG_fE2Low1Dpt8In             28      // int16_t
#define LOG_fE2Low2Dpt8In             30      // int16_t
#define LOG_fE2LowDpt8Fix             26      // int16_t
#define LOG_fE2LowDpt9                26      // float
#define LOG_fE2HighDpt9               30      // float
#define LOG_fE2LowDpt9Fix             26      // float
#define LOG_fE2Low0Dpt17              26      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt17              27      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt17              28      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt17              29      // 8 Bits, Bit 7-0
#define LOG_fE2Low4Dpt17              30      // 8 Bits, Bit 7-0
#define LOG_fE2Low5Dpt17              31      // 8 Bits, Bit 7-0
#define LOG_fE2Low6Dpt17              32      // 8 Bits, Bit 7-0
#define LOG_fE2Low7Dpt17              33      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt17Fix            26      // 8 Bits, Bit 7-0
#define LOG_fE2LowDptRGB              26      // int32_t
#define LOG_fE2HighDptRGB             30      // int32_t
#define LOG_fE2LowDptRGBFix           26      // int32_t
#define LOG_fTd1Value                 18      // 1 Bit, Bit 7
#define     LOG_fTd1ValueMask 0x80
#define     LOG_fTd1ValueShift 7
#define LOG_fTd1HourAbs               18      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourAbsMask 0x3E
#define     LOG_fTd1HourAbsShift 1
#define LOG_fTd1HourRel               18      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourRelMask 0x3E
#define     LOG_fTd1HourRelShift 1
#define LOG_fTd1MinuteAbs             18      // 6 Bits, Bit 0--5
#define LOG_fTd1MinuteRel             18      // 6 Bits, Bit 0--5
#define LOG_fTd1Weekday               19      // 3 Bits, Bit 2-0
#define     LOG_fTd1WeekdayMask 0x07
#define     LOG_fTd1WeekdayShift 0
#define LOG_fTd2Value                 20      // 1 Bit, Bit 7
#define     LOG_fTd2ValueMask 0x80
#define     LOG_fTd2ValueShift 7
#define LOG_fTd2HourAbs               20      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourAbsMask 0x3E
#define     LOG_fTd2HourAbsShift 1
#define LOG_fTd2HourRel               20      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourRelMask 0x3E
#define     LOG_fTd2HourRelShift 1
#define LOG_fTd2MinuteAbs             20      // 6 Bits, Bit 0--5
#define LOG_fTd2MinuteRel             20      // 6 Bits, Bit 0--5
#define LOG_fTd2Weekday               21      // 3 Bits, Bit 2-0
#define     LOG_fTd2WeekdayMask 0x07
#define     LOG_fTd2WeekdayShift 0
#define LOG_fTd3Value                 22      // 1 Bit, Bit 7
#define     LOG_fTd3ValueMask 0x80
#define     LOG_fTd3ValueShift 7
#define LOG_fTd3HourAbs               22      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourAbsMask 0x3E
#define     LOG_fTd3HourAbsShift 1
#define LOG_fTd3HourRel               22      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourRelMask 0x3E
#define     LOG_fTd3HourRelShift 1
#define LOG_fTd3MinuteAbs             22      // 6 Bits, Bit 0--5
#define LOG_fTd3MinuteRel             22      // 6 Bits, Bit 0--5
#define LOG_fTd3Weekday               23      // 3 Bits, Bit 2-0
#define     LOG_fTd3WeekdayMask 0x07
#define     LOG_fTd3WeekdayShift 0
#define LOG_fTd4Value                 24      // 1 Bit, Bit 7
#define     LOG_fTd4ValueMask 0x80
#define     LOG_fTd4ValueShift 7
#define LOG_fTd4HourAbs               24      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourAbsMask 0x3E
#define     LOG_fTd4HourAbsShift 1
#define LOG_fTd4HourRel               24      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourRelMask 0x3E
#define     LOG_fTd4HourRelShift 1
#define LOG_fTd4MinuteAbs             24      // 6 Bits, Bit 0--5
#define LOG_fTd4MinuteRel             24      // 6 Bits, Bit 0--5
#define LOG_fTd4Weekday               25      // 3 Bits, Bit 2-0
#define     LOG_fTd4WeekdayMask 0x07
#define     LOG_fTd4WeekdayShift 0
#define LOG_fTd5Value                 26      // 1 Bit, Bit 7
#define     LOG_fTd5ValueMask 0x80
#define     LOG_fTd5ValueShift 7
#define LOG_fTd5HourAbs               26      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourAbsMask 0x3E
#define     LOG_fTd5HourAbsShift 1
#define LOG_fTd5HourRel               26      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourRelMask 0x3E
#define     LOG_fTd5HourRelShift 1
#define LOG_fTd5MinuteAbs             26      // 6 Bits, Bit 0--5
#define LOG_fTd5MinuteRel             26      // 6 Bits, Bit 0--5
#define LOG_fTd5Weekday               27      // 3 Bits, Bit 2-0
#define     LOG_fTd5WeekdayMask 0x07
#define     LOG_fTd5WeekdayShift 0
#define LOG_fTd6Value                 28      // 1 Bit, Bit 7
#define     LOG_fTd6ValueMask 0x80
#define     LOG_fTd6ValueShift 7
#define LOG_fTd6HourAbs               28      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourAbsMask 0x3E
#define     LOG_fTd6HourAbsShift 1
#define LOG_fTd6HourRel               28      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourRelMask 0x3E
#define     LOG_fTd6HourRelShift 1
#define LOG_fTd6MinuteAbs             28      // 6 Bits, Bit 0--5
#define LOG_fTd6MinuteRel             28      // 6 Bits, Bit 0--5
#define LOG_fTd6Weekday               29      // 3 Bits, Bit 2-0
#define     LOG_fTd6WeekdayMask 0x07
#define     LOG_fTd6WeekdayShift 0
#define LOG_fTd7Value                 30      // 1 Bit, Bit 7
#define     LOG_fTd7ValueMask 0x80
#define     LOG_fTd7ValueShift 7
#define LOG_fTd7HourAbs               30      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourAbsMask 0x3E
#define     LOG_fTd7HourAbsShift 1
#define LOG_fTd7HourRel               30      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourRelMask 0x3E
#define     LOG_fTd7HourRelShift 1
#define LOG_fTd7MinuteAbs             30      // 6 Bits, Bit 0--5
#define LOG_fTd7MinuteRel             30      // 6 Bits, Bit 0--5
#define LOG_fTd7Weekday               31      // 3 Bits, Bit 2-0
#define     LOG_fTd7WeekdayMask 0x07
#define     LOG_fTd7WeekdayShift 0
#define LOG_fTd8Value                 32      // 1 Bit, Bit 7
#define     LOG_fTd8ValueMask 0x80
#define     LOG_fTd8ValueShift 7
#define LOG_fTd8HourAbs               32      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourAbsMask 0x3E
#define     LOG_fTd8HourAbsShift 1
#define LOG_fTd8HourRel               32      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourRelMask 0x3E
#define     LOG_fTd8HourRelShift 1
#define LOG_fTd8MinuteAbs             32      // 6 Bits, Bit 0--5
#define LOG_fTd8MinuteRel             32      // 6 Bits, Bit 0--5
#define LOG_fTd8Weekday               33      // 3 Bits, Bit 2-0
#define     LOG_fTd8WeekdayMask 0x07
#define     LOG_fTd8WeekdayShift 0
#define LOG_fTy1Weekday1              26      // 1 Bit, Bit 7
#define     LOG_fTy1Weekday1Mask 0x80
#define     LOG_fTy1Weekday1Shift 7
#define LOG_fTy1Weekday2              26      // 1 Bit, Bit 6
#define     LOG_fTy1Weekday2Mask 0x40
#define     LOG_fTy1Weekday2Shift 6
#define LOG_fTy1Weekday3              26      // 1 Bit, Bit 5
#define     LOG_fTy1Weekday3Mask 0x20
#define     LOG_fTy1Weekday3Shift 5
#define LOG_fTy1Weekday4              26      // 1 Bit, Bit 4
#define     LOG_fTy1Weekday4Mask 0x10
#define     LOG_fTy1Weekday4Shift 4
#define LOG_fTy1Weekday5              26      // 1 Bit, Bit 3
#define     LOG_fTy1Weekday5Mask 0x08
#define     LOG_fTy1Weekday5Shift 3
#define LOG_fTy1Weekday6              26      // 1 Bit, Bit 2
#define     LOG_fTy1Weekday6Mask 0x04
#define     LOG_fTy1Weekday6Shift 2
#define LOG_fTy1Weekday7              26      // 1 Bit, Bit 1
#define     LOG_fTy1Weekday7Mask 0x02
#define     LOG_fTy1Weekday7Shift 1
#define LOG_fTy1Day                   26      // 7 Bits, Bit 7-1
#define LOG_fTy1IsWeekday             26      // 1 Bit, Bit 0
#define     LOG_fTy1IsWeekdayMask 0x01
#define     LOG_fTy1IsWeekdayShift 0
#define LOG_fTy1Month                 27      // 4 Bits, Bit 7-4
#define     LOG_fTy1MonthMask 0xF0
#define     LOG_fTy1MonthShift 4
#define LOG_fTy2Weekday1              28      // 1 Bit, Bit 7
#define     LOG_fTy2Weekday1Mask 0x80
#define     LOG_fTy2Weekday1Shift 7
#define LOG_fTy2Weekday2              28      // 1 Bit, Bit 6
#define     LOG_fTy2Weekday2Mask 0x40
#define     LOG_fTy2Weekday2Shift 6
#define LOG_fTy2Weekday3              28      // 1 Bit, Bit 5
#define     LOG_fTy2Weekday3Mask 0x20
#define     LOG_fTy2Weekday3Shift 5
#define LOG_fTy2Weekday4              28      // 1 Bit, Bit 4
#define     LOG_fTy2Weekday4Mask 0x10
#define     LOG_fTy2Weekday4Shift 4
#define LOG_fTy2Weekday5              28      // 1 Bit, Bit 3
#define     LOG_fTy2Weekday5Mask 0x08
#define     LOG_fTy2Weekday5Shift 3
#define LOG_fTy2Weekday6              28      // 1 Bit, Bit 2
#define     LOG_fTy2Weekday6Mask 0x04
#define     LOG_fTy2Weekday6Shift 2
#define LOG_fTy2Weekday7              28      // 1 Bit, Bit 1
#define     LOG_fTy2Weekday7Mask 0x02
#define     LOG_fTy2Weekday7Shift 1
#define LOG_fTy2Day                   28      // 7 Bits, Bit 7-1
#define LOG_fTy2IsWeekday             28      // 1 Bit, Bit 0
#define     LOG_fTy2IsWeekdayMask 0x01
#define     LOG_fTy2IsWeekdayShift 0
#define LOG_fTy2Month                 29      // 4 Bits, Bit 7-4
#define     LOG_fTy2MonthMask 0xF0
#define     LOG_fTy2MonthShift 4
#define LOG_fTy3Weekday1              30      // 1 Bit, Bit 7
#define     LOG_fTy3Weekday1Mask 0x80
#define     LOG_fTy3Weekday1Shift 7
#define LOG_fTy3Weekday2              30      // 1 Bit, Bit 6
#define     LOG_fTy3Weekday2Mask 0x40
#define     LOG_fTy3Weekday2Shift 6
#define LOG_fTy3Weekday3              30      // 1 Bit, Bit 5
#define     LOG_fTy3Weekday3Mask 0x20
#define     LOG_fTy3Weekday3Shift 5
#define LOG_fTy3Weekday4              30      // 1 Bit, Bit 4
#define     LOG_fTy3Weekday4Mask 0x10
#define     LOG_fTy3Weekday4Shift 4
#define LOG_fTy3Weekday5              30      // 1 Bit, Bit 3
#define     LOG_fTy3Weekday5Mask 0x08
#define     LOG_fTy3Weekday5Shift 3
#define LOG_fTy3Weekday6              30      // 1 Bit, Bit 2
#define     LOG_fTy3Weekday6Mask 0x04
#define     LOG_fTy3Weekday6Shift 2
#define LOG_fTy3Weekday7              30      // 1 Bit, Bit 1
#define     LOG_fTy3Weekday7Mask 0x02
#define     LOG_fTy3Weekday7Shift 1
#define LOG_fTy3Day                   30      // 7 Bits, Bit 7-1
#define LOG_fTy3IsWeekday             30      // 1 Bit, Bit 0
#define     LOG_fTy3IsWeekdayMask 0x01
#define     LOG_fTy3IsWeekdayShift 0
#define LOG_fTy3Month                 31      // 4 Bits, Bit 7-4
#define     LOG_fTy3MonthMask 0xF0
#define     LOG_fTy3MonthShift 4
#define LOG_fTy4Weekday1              32      // 1 Bit, Bit 7
#define     LOG_fTy4Weekday1Mask 0x80
#define     LOG_fTy4Weekday1Shift 7
#define LOG_fTy4Weekday2              32      // 1 Bit, Bit 6
#define     LOG_fTy4Weekday2Mask 0x40
#define     LOG_fTy4Weekday2Shift 6
#define LOG_fTy4Weekday3              32      // 1 Bit, Bit 5
#define     LOG_fTy4Weekday3Mask 0x20
#define     LOG_fTy4Weekday3Shift 5
#define LOG_fTy4Weekday4              32      // 1 Bit, Bit 4
#define     LOG_fTy4Weekday4Mask 0x10
#define     LOG_fTy4Weekday4Shift 4
#define LOG_fTy4Weekday5              32      // 1 Bit, Bit 3
#define     LOG_fTy4Weekday5Mask 0x08
#define     LOG_fTy4Weekday5Shift 3
#define LOG_fTy4Weekday6              32      // 1 Bit, Bit 2
#define     LOG_fTy4Weekday6Mask 0x04
#define     LOG_fTy4Weekday6Shift 2
#define LOG_fTy4Weekday7              32      // 1 Bit, Bit 1
#define     LOG_fTy4Weekday7Mask 0x02
#define     LOG_fTy4Weekday7Shift 1
#define LOG_fTy4Day                   32      // 7 Bits, Bit 7-1
#define LOG_fTy4IsWeekday             32      // 1 Bit, Bit 0
#define     LOG_fTy4IsWeekdayMask 0x01
#define     LOG_fTy4IsWeekdayShift 0
#define LOG_fTy4Month                 33      // 4 Bits, Bit 7-4
#define     LOG_fTy4MonthMask 0xF0
#define     LOG_fTy4MonthShift 4
#define LOG_fI1                       34      // 4 Bits, Bit 7-4
#define     LOG_fI1Mask 0xF0
#define     LOG_fI1Shift 4
#define LOG_fI2                       34      // 4 Bits, Bit 3-0
#define     LOG_fI2Mask 0x0F
#define     LOG_fI2Shift 0
#define LOG_fI1Function               35      // uint8_t
#define LOG_fI2Function               36      // uint8_t
#define LOG_fOStairtimeBase           37      // 2 Bits, Bit 7-6
#define     LOG_fOStairtimeBaseMask 0xC0
#define     LOG_fOStairtimeBaseShift 6
#define LOG_fOStairtimeTime           37      // uint14_t
#define LOG_fOBlinkBase               39      // 2 Bits, Bit 7-6
#define     LOG_fOBlinkBaseMask 0xC0
#define     LOG_fOBlinkBaseShift 6
#define LOG_fOBlinkTime               39      // uint14_t
#define LOG_fODelay                   41      // 1 Bit, Bit 7
#define     LOG_fODelayMask 0x80
#define     LOG_fODelayShift 7
#define LOG_fODelayOnRepeat           41      // 2 Bits, Bit 6-5
#define     LOG_fODelayOnRepeatMask 0x60
#define     LOG_fODelayOnRepeatShift 5
#define LOG_fODelayOnReset            41      // 1 Bit, Bit 4
#define     LOG_fODelayOnResetMask 0x10
#define     LOG_fODelayOnResetShift 4
#define LOG_fODelayOffRepeat          41      // 2 Bits, Bit 3-2
#define     LOG_fODelayOffRepeatMask 0x0C
#define     LOG_fODelayOffRepeatShift 2
#define LOG_fODelayOffReset           41      // 1 Bit, Bit 1
#define     LOG_fODelayOffResetMask 0x02
#define     LOG_fODelayOffResetShift 1
#define LOG_fODelayOnBase             42      // 2 Bits, Bit 7-6
#define     LOG_fODelayOnBaseMask 0xC0
#define     LOG_fODelayOnBaseShift 6
#define LOG_fODelayOnTime             42      // uint14_t
#define LOG_fODelayOffBase            44      // 2 Bits, Bit 7-6
#define     LOG_fODelayOffBaseMask 0xC0
#define     LOG_fODelayOffBaseShift 6
#define LOG_fODelayOffTime            44      // uint14_t
#define LOG_fOStair                   46      // 1 Bit, Bit 7
#define     LOG_fOStairMask 0x80
#define     LOG_fOStairShift 7
#define LOG_fORetrigger               46      // 1 Bit, Bit 6
#define     LOG_fORetriggerMask 0x40
#define     LOG_fORetriggerShift 6
#define LOG_fOStairOff                46      // 1 Bit, Bit 5
#define     LOG_fOStairOffMask 0x20
#define     LOG_fOStairOffShift 5
#define LOG_fORepeat                  46      // 1 Bit, Bit 4
#define     LOG_fORepeatMask 0x10
#define     LOG_fORepeatShift 4
#define LOG_fOOutputFilter            46      // 2 Bits, Bit 3-2
#define     LOG_fOOutputFilterMask 0x0C
#define     LOG_fOOutputFilterShift 2
#define LOG_fORepeatOnBase            47      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOnBaseMask 0xC0
#define     LOG_fORepeatOnBaseShift 6
#define LOG_fORepeatOnTime            47      // uint14_t
#define LOG_fORepeatOffBase           49      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOffBaseMask 0xC0
#define     LOG_fORepeatOffBaseShift 6
#define LOG_fORepeatOffTime           49      // uint14_t
#define LOG_fODpt                     51      // 8 Bits, Bit 7-0
#define LOG_fOOn                      52      // 8 Bits, Bit 7-0
#define LOG_fOOnBuzzer                52      // 8 Bits, Bit 7-0
#define LOG_fOOnLed                   52      // 8 Bits, Bit 7-0
#define LOG_fOOnAll                   52      // 8 Bits, Bit 7-0
#define LOG_fOOnTone                  53      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt1                  53      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt2                  53      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt5                  53      // uint8_t
#define LOG_fOOnDpt5001               53      // uint8_t
#define LOG_fOOnDpt6                  53      // int8_t
#define LOG_fOOnDpt7                  53      // uint16_t
#define LOG_fOOnDpt8                  53      // int16_t
#define LOG_fOOnDpt9                  53      // float
#define LOG_fOOnDpt16                 53      // char*, 14 Byte
#define LOG_fOOnDpt17                 53      // 8 Bits, Bit 7-0
#define LOG_fOOnRGB                   53      // color, uint, 3 Byte
#define LOG_fOOnPAArea                53      // 4 Bits, Bit 7-4
#define     LOG_fOOnPAAreaMask 0xF0
#define     LOG_fOOnPAAreaShift 4
#define LOG_fOOnPALine                53      // 4 Bits, Bit 3-0
#define     LOG_fOOnPALineMask 0x0F
#define     LOG_fOOnPALineShift 0
#define LOG_fOOnPADevice              54      // uint8_t
#define LOG_fOOnFunction              53      // 8 Bits, Bit 7-0
#define LOG_fOOff                     67      // 8 Bits, Bit 7-0
#define LOG_fOOffBuzzer               67      // 8 Bits, Bit 7-0
#define LOG_fOOffLed                  67      // 8 Bits, Bit 7-0
#define LOG_fOOffAll                  67      // 8 Bits, Bit 7-0
#define LOG_fOOffTone                 68      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt1                 68      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt2                 68      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt5                 68      // uint8_t
#define LOG_fOOffDpt5001              68      // uint8_t
#define LOG_fOOffDpt6                 68      // int8_t
#define LOG_fOOffDpt7                 68      // uint16_t
#define LOG_fOOffDpt8                 68      // int16_t
#define LOG_fOOffDpt9                 68      // float
#define LOG_fOOffDpt16                68      // char*, 14 Byte
#define LOG_fOOffDpt17                68      // 8 Bits, Bit 7-0
#define LOG_fOOffRGB                  68      // color, uint, 3 Byte
#define LOG_fOOffPAArea               68      // 4 Bits, Bit 7-4
#define     LOG_fOOffPAAreaMask 0xF0
#define     LOG_fOOffPAAreaShift 4
#define LOG_fOOffPALine               68      // 4 Bits, Bit 3-0
#define     LOG_fOOffPALineMask 0x0F
#define     LOG_fOOffPALineShift 0
#define LOG_fOOffPADevice             69      // uint8_t
#define LOG_fOOffFunction             68      // 8 Bits, Bit 7-0
#define LOG_fE1UseOtherKO             82      // 1 Bit, Bit 7
#define     LOG_fE1UseOtherKOMask 0x80
#define     LOG_fE1UseOtherKOShift 7
#define LOG_fE1OtherKO                82      // uint15_t
#define LOG_fE2UseOtherKO             84      // 1 Bit, Bit 7
#define     LOG_fE2UseOtherKOMask 0x80
#define     LOG_fE2UseOtherKOShift 7
#define LOG_fE2OtherKO                84      // uint15_t

// Communication objects per channel (multiple occurrence)
#define LOG_KoOffset 450
#define LOG_KoBlockSize 3
#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

#define PM_ChannelCount 20

// Parameter per channel
#define PM_ParamBlockOffset 2628
#define PM_ParamBlockSize 133
#define PM_pPresenceInputs            0      // 3 Bits, Bit 7-5
#define     PM_pPresenceInputsMask 0xE0
#define     PM_pPresenceInputsShift 5
#define PM_pPresenceType              0      // 1 Bit, Bit 4
#define     PM_pPresenceTypeMask 0x10
#define     PM_pPresenceTypeShift 4
#define PM_pMoveType                  0      // 1 Bit, Bit 3
#define     PM_pMoveTypeMask 0x08
#define     PM_pMoveTypeShift 3
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
#define PM_pBrightnessIntern          2      // 1 Bit, Bit 6
#define     PM_pBrightnessInternMask 0x40
#define     PM_pBrightnessInternShift 6
#define PM_pExternalSupportsReset     2      // 1 Bit, Bit 5
#define     PM_pExternalSupportsResetMask 0x20
#define     PM_pExternalSupportsResetShift 5
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
#define PM_pPresenceUsage             3      // 2 Bits, Bit 3-2
#define     PM_pPresenceUsageMask 0x0C
#define     PM_pPresenceUsageShift 2
#define PM_pPresenceUsagePIR          3      // 2 Bits, Bit 3-2
#define     PM_pPresenceUsagePIRMask 0x0C
#define     PM_pPresenceUsagePIRShift 2
#define PM_pAutoOffIsLeave            3      // 1 Bit, Bit 1
#define     PM_pAutoOffIsLeaveMask 0x02
#define     PM_pAutoOffIsLeaveShift 1
#define PM_pManualModeKeyCount        3      // 1 Bit, Bit 0
#define     PM_pManualModeKeyCountMask 0x01
#define     PM_pManualModeKeyCountShift 0
#define PM_pBrightnessRead            4      // 1 Bit, Bit 7
#define     PM_pBrightnessReadMask 0x80
#define     PM_pBrightnessReadShift 7
#define PM_pStartReadLux              4      // 1 Bit, Bit 6
#define     PM_pStartReadLuxMask 0x40
#define     PM_pStartReadLuxShift 6
#define PM_pStartReadPresence1        4      // 1 Bit, Bit 5
#define     PM_pStartReadPresence1Mask 0x20
#define     PM_pStartReadPresence1Shift 5
#define PM_pStartReadPresence2        4      // 1 Bit, Bit 4
#define     PM_pStartReadPresence2Mask 0x10
#define     PM_pStartReadPresence2Shift 4
#define PM_pStartReadAktorState       4      // 1 Bit, Bit 3
#define     PM_pStartReadAktorStateMask 0x08
#define     PM_pStartReadAktorStateShift 3
#define PM_pStartReadLock             4      // 1 Bit, Bit 2
#define     PM_pStartReadLockMask 0x04
#define     PM_pStartReadLockShift 2
#define PM_pStartReadDayPhase         4      // 1 Bit, Bit 1
#define     PM_pStartReadDayPhaseMask 0x02
#define     PM_pStartReadDayPhaseShift 1
#define PM_pStartReadScene            4      // 1 Bit, Bit 0
#define     PM_pStartReadSceneMask 0x01
#define     PM_pStartReadSceneShift 0
#define PM_pLeaveRoomModeAll          5      // 3 Bits, Bit 7-5
#define     PM_pLeaveRoomModeAllMask 0xE0
#define     PM_pLeaveRoomModeAllShift 5
#define PM_pLeaveRoomModeMove         5      // 3 Bits, Bit 7-5
#define     PM_pLeaveRoomModeMoveMask 0xE0
#define     PM_pLeaveRoomModeMoveShift 5
#define PM_pLeaveRoomModeReset        5      // 3 Bits, Bit 7-5
#define     PM_pLeaveRoomModeResetMask 0xE0
#define     PM_pLeaveRoomModeResetShift 5
#define PM_pChannelDelayBase          6      // 2 Bits, Bit 7-6
#define     PM_pChannelDelayBaseMask 0xC0
#define     PM_pChannelDelayBaseShift 6
#define PM_pChannelDelayTime          6      // uint14_t
#define PM_pLockFallbackBase          8      // 2 Bits, Bit 7-6
#define     PM_pLockFallbackBaseMask 0xC0
#define     PM_pLockFallbackBaseShift 6
#define PM_pLockFallbackTime          8      // uint14_t
#define PM_pDowntimeOffBase          10      // 2 Bits, Bit 7-6
#define     PM_pDowntimeOffBaseMask 0xC0
#define     PM_pDowntimeOffBaseShift 6
#define PM_pDowntimeOffTime          10      // uint14_t
#define PM_pAdaptiveDelayBase        12      // 2 Bits, Bit 7-6
#define     PM_pAdaptiveDelayBaseMask 0xC0
#define     PM_pAdaptiveDelayBaseShift 6
#define PM_pAdaptiveDelayTime        12      // uint14_t
#define PM_pPhase1Scene              14      // 8 Bits, Bit 7-0
#define PM_pPhase2Scene              15      // 8 Bits, Bit 7-0
#define PM_pPhase3Scene              16      // 8 Bits, Bit 7-0
#define PM_pPhase4Scene              17      // 8 Bits, Bit 7-0
#define PM_pScene0                   18      // 8 Bits, Bit 7-0
#define PM_pScene1                   19      // 8 Bits, Bit 7-0
#define PM_pScene2                   20      // 8 Bits, Bit 7-0
#define PM_pScene3                   21      // 8 Bits, Bit 7-0
#define PM_pScene4                   22      // 8 Bits, Bit 7-0
#define PM_pScene5                   23      // 8 Bits, Bit 7-0
#define PM_pScene6                   24      // 8 Bits, Bit 7-0
#define PM_pScene7                   25      // 8 Bits, Bit 7-0
#define PM_pScene8                   26      // 8 Bits, Bit 7-0
#define PM_pScene9                   27      // 8 Bits, Bit 7-0
#define PM_pSceneAction0             28      // 4 Bits, Bit 7-4
#define     PM_pSceneAction0Mask 0xF0
#define     PM_pSceneAction0Shift 4
#define PM_pSceneAction1             28      // 4 Bits, Bit 3-0
#define     PM_pSceneAction1Mask 0x0F
#define     PM_pSceneAction1Shift 0
#define PM_pSceneAction2             29      // 4 Bits, Bit 7-4
#define     PM_pSceneAction2Mask 0xF0
#define     PM_pSceneAction2Shift 4
#define PM_pSceneAction3             29      // 4 Bits, Bit 3-0
#define     PM_pSceneAction3Mask 0x0F
#define     PM_pSceneAction3Shift 0
#define PM_pSceneAction4             30      // 4 Bits, Bit 7-4
#define     PM_pSceneAction4Mask 0xF0
#define     PM_pSceneAction4Shift 4
#define PM_pSceneAction5             30      // 4 Bits, Bit 3-0
#define     PM_pSceneAction5Mask 0x0F
#define     PM_pSceneAction5Shift 0
#define PM_pSceneAction6             31      // 4 Bits, Bit 7-4
#define     PM_pSceneAction6Mask 0xF0
#define     PM_pSceneAction6Shift 4
#define PM_pSceneAction7             31      // 4 Bits, Bit 3-0
#define     PM_pSceneAction7Mask 0x0F
#define     PM_pSceneAction7Shift 0
#define PM_pSceneAction8             32      // 4 Bits, Bit 7-4
#define     PM_pSceneAction8Mask 0xF0
#define     PM_pSceneAction8Shift 4
#define PM_pSceneAction9             32      // 4 Bits, Bit 3-0
#define     PM_pSceneAction9Mask 0x0F
#define     PM_pSceneAction9Shift 0
#define PM_pIntLux                   33      // 1 Bit, Bit 7
#define     PM_pIntLuxMask 0x80
#define     PM_pIntLuxShift 7
#define PM_pNumLux                   33      // uint15_t
#define PM_pIntPresence1             35      // 1 Bit, Bit 7
#define     PM_pIntPresence1Mask 0x80
#define     PM_pIntPresence1Shift 7
#define PM_pNumPresence1             35      // uint15_t
#define PM_pIntPresence2             37      // 1 Bit, Bit 7
#define     PM_pIntPresence2Mask 0x80
#define     PM_pIntPresence2Shift 7
#define PM_pNumPresence2             37      // uint15_t
#define PM_pIntSetAuto               39      // 1 Bit, Bit 7
#define     PM_pIntSetAutoMask 0x80
#define     PM_pIntSetAutoShift 7
#define PM_pNumSetAuto               39      // uint15_t
#define PM_pIntSetManual             41      // 1 Bit, Bit 7
#define     PM_pIntSetManualMask 0x80
#define     PM_pIntSetManualShift 7
#define PM_pNumSetManual             41      // uint15_t
#define PM_pIntActorState            43      // 1 Bit, Bit 7
#define     PM_pIntActorStateMask 0x80
#define     PM_pIntActorStateShift 7
#define PM_pNumActorState            43      // uint15_t
#define PM_pIntLock                  45      // 1 Bit, Bit 7
#define     PM_pIntLockMask 0x80
#define     PM_pIntLockShift 7
#define PM_pNumLock                  45      // uint15_t
#define PM_pIntReset                 47      // 1 Bit, Bit 7
#define     PM_pIntResetMask 0x80
#define     PM_pIntResetShift 7
#define PM_pNumReset                 47      // uint15_t
#define PM_pIntDayPhase              49      // 1 Bit, Bit 7
#define     PM_pIntDayPhaseMask 0x80
#define     PM_pIntDayPhaseShift 7
#define PM_pNumDayPhase              49      // uint15_t
#define PM_pIntScene                 51      // 1 Bit, Bit 7
#define     PM_pIntSceneMask 0x80
#define     PM_pIntSceneShift 7
#define PM_pNumScene                 51      // uint15_t
#define PM_pABrightnessAuto          53      // 2 Bits, Bit 7-6
#define     PM_pABrightnessAutoMask 0xC0
#define     PM_pABrightnessAutoShift 6
#define PM_pAPresenceShort           53      // 1 Bit, Bit 5
#define     PM_pAPresenceShortMask 0x20
#define     PM_pAPresenceShortShift 5
#define PM_pALockHardwareLEDs        53      // 1 Bit, Bit 4
#define     PM_pALockHardwareLEDsMask 0x10
#define     PM_pALockHardwareLEDsShift 4
#define PM_pAOutput1Filter           53      // 2 Bits, Bit 3-2
#define     PM_pAOutput1FilterMask 0x0C
#define     PM_pAOutput1FilterShift 2
#define PM_pAOutput2Filter           53      // 2 Bits, Bit 1-0
#define     PM_pAOutput2FilterMask 0x03
#define     PM_pAOutput2FilterShift 0
#define PM_pAManualWithPresence      54      // 1 Bit, Bit 7
#define     PM_pAManualWithPresenceMask 0x80
#define     PM_pAManualWithPresenceShift 7
#define PM_pAPresenceShortNoSwitch   54      // 1 Bit, Bit 6
#define     PM_pAPresenceShortNoSwitchMask 0x40
#define     PM_pAPresenceShortNoSwitchShift 6
#define PM_pAPresenceDelayBase       55      // 2 Bits, Bit 7-6
#define     PM_pAPresenceDelayBaseMask 0xC0
#define     PM_pAPresenceDelayBaseShift 6
#define PM_pAPresenceDelayTime       55      // uint14_t
#define PM_pAPresenceShortDurationBase 57      // 2 Bits, Bit 7-6
#define     PM_pAPresenceShortDurationBaseMask 0xC0
#define     PM_pAPresenceShortDurationBaseShift 6
#define PM_pAPresenceShortDurationTime 57      // uint14_t
#define PM_pAPresenceShortDelayBase  59      // 2 Bits, Bit 7-6
#define     PM_pAPresenceShortDelayBaseMask 0xC0
#define     PM_pAPresenceShortDelayBaseShift 6
#define PM_pAPresenceShortDelayTime  59      // uint14_t
#define PM_pABrightnessOffDelayBase  61      // 2 Bits, Bit 7-6
#define     PM_pABrightnessOffDelayBaseMask 0xC0
#define     PM_pABrightnessOffDelayBaseShift 6
#define PM_pABrightnessOffDelayTime  61      // uint14_t
#define PM_pAManualFallbackDelayBase 63      // 2 Bits, Bit 7-6
#define     PM_pAManualFallbackDelayBaseMask 0xC0
#define     PM_pAManualFallbackDelayBaseShift 6
#define PM_pAManualFallbackDelayTime 63      // uint14_t
#define PM_pABrightnessOn            65      // uint16_t
#define PM_pABrightnessDelta         67      // uint16_t
#define PM_pAOutput1On               69      // 8 Bits, Bit 7-0
#define PM_pAOutput1OnValue          69      // uint8_t
#define PM_pAOutput1OnScene          69      // 8 Bits, Bit 7-0
#define PM_pAOutput1OnDim            69      // uint8_t
#define PM_pAOutput1Off              70      // 8 Bits, Bit 7-0
#define PM_pAOutput1OffValue         70      // uint8_t
#define PM_pAOutput1OffScene         70      // 8 Bits, Bit 7-0
#define PM_pAOutput1OffDim           70      // uint8_t
#define PM_pAOutput2On               71      // 8 Bits, Bit 7-0
#define PM_pAOutput2OnValue          71      // uint8_t
#define PM_pAOutput2OnScene          71      // 8 Bits, Bit 7-0
#define PM_pAOutput2OnDim            71      // uint8_t
#define PM_pAOutput2Off              72      // 8 Bits, Bit 7-0
#define PM_pAOutput2OffValue         72      // uint8_t
#define PM_pAOutput2OffScene         72      // 8 Bits, Bit 7-0
#define PM_pAOutput2OffDim           72      // uint8_t
#define PM_pBBrightnessAuto          73      // 2 Bits, Bit 7-6
#define     PM_pBBrightnessAutoMask 0xC0
#define     PM_pBBrightnessAutoShift 6
#define PM_pBPresenceShort           73      // 1 Bit, Bit 5
#define     PM_pBPresenceShortMask 0x20
#define     PM_pBPresenceShortShift 5
#define PM_pBLockHardwareLEDs        73      // 1 Bit, Bit 4
#define     PM_pBLockHardwareLEDsMask 0x10
#define     PM_pBLockHardwareLEDsShift 4
#define PM_pBOutput1Filter           73      // 2 Bits, Bit 3-2
#define     PM_pBOutput1FilterMask 0x0C
#define     PM_pBOutput1FilterShift 2
#define PM_pBOutput2Filter           73      // 2 Bits, Bit 1-0
#define     PM_pBOutput2FilterMask 0x03
#define     PM_pBOutput2FilterShift 0
#define PM_pBManualWithPresence      74      // 1 Bit, Bit 7
#define     PM_pBManualWithPresenceMask 0x80
#define     PM_pBManualWithPresenceShift 7
#define PM_pBPresenceShortNoSwitch   74      // 1 Bit, Bit 6
#define     PM_pBPresenceShortNoSwitchMask 0x40
#define     PM_pBPresenceShortNoSwitchShift 6
#define PM_pBPresenceDelayBase       75      // 2 Bits, Bit 7-6
#define     PM_pBPresenceDelayBaseMask 0xC0
#define     PM_pBPresenceDelayBaseShift 6
#define PM_pBPresenceDelayTime       75      // uint14_t
#define PM_pBPresenceShortDurationBase 77      // 2 Bits, Bit 7-6
#define     PM_pBPresenceShortDurationBaseMask 0xC0
#define     PM_pBPresenceShortDurationBaseShift 6
#define PM_pBPresenceShortDurationTime 77      // uint14_t
#define PM_pBPresenceShortDelayBase  79      // 2 Bits, Bit 7-6
#define     PM_pBPresenceShortDelayBaseMask 0xC0
#define     PM_pBPresenceShortDelayBaseShift 6
#define PM_pBPresenceShortDelayTime  79      // uint14_t
#define PM_pBBrightnessOffDelayBase  81      // 2 Bits, Bit 7-6
#define     PM_pBBrightnessOffDelayBaseMask 0xC0
#define     PM_pBBrightnessOffDelayBaseShift 6
#define PM_pBBrightnessOffDelayTime  81      // uint14_t
#define PM_pBManualFallbackDelayBase 83      // 2 Bits, Bit 7-6
#define     PM_pBManualFallbackDelayBaseMask 0xC0
#define     PM_pBManualFallbackDelayBaseShift 6
#define PM_pBManualFallbackDelayTime 83      // uint14_t
#define PM_pBBrightnessOn            85      // uint16_t
#define PM_pBBrightnessDelta         87      // uint16_t
#define PM_pBOutput1On               89      // 8 Bits, Bit 7-0
#define PM_pBOutput1OnValue          89      // uint8_t
#define PM_pBOutput1OnScene          89      // 8 Bits, Bit 7-0
#define PM_pBOutput1OnDim            89      // uint8_t
#define PM_pBOutput1Off              90      // 8 Bits, Bit 7-0
#define PM_pBOutput1OffValue         90      // uint8_t
#define PM_pBOutput1OffScene         90      // 8 Bits, Bit 7-0
#define PM_pBOutput1OffDim           90      // uint8_t
#define PM_pBOutput2On               91      // 8 Bits, Bit 7-0
#define PM_pBOutput2OnValue          91      // uint8_t
#define PM_pBOutput2OnScene          91      // 8 Bits, Bit 7-0
#define PM_pBOutput2OnDim            91      // uint8_t
#define PM_pBOutput2Off              92      // 8 Bits, Bit 7-0
#define PM_pBOutput2OffValue         92      // uint8_t
#define PM_pBOutput2OffScene         92      // 8 Bits, Bit 7-0
#define PM_pBOutput2OffDim           92      // uint8_t
#define PM_pCBrightnessAuto          93      // 2 Bits, Bit 7-6
#define     PM_pCBrightnessAutoMask 0xC0
#define     PM_pCBrightnessAutoShift 6
#define PM_pCPresenceShort           93      // 1 Bit, Bit 5
#define     PM_pCPresenceShortMask 0x20
#define     PM_pCPresenceShortShift 5
#define PM_pCLockHardwareLEDs        93      // 1 Bit, Bit 4
#define     PM_pCLockHardwareLEDsMask 0x10
#define     PM_pCLockHardwareLEDsShift 4
#define PM_pCOutput1Filter           93      // 2 Bits, Bit 3-2
#define     PM_pCOutput1FilterMask 0x0C
#define     PM_pCOutput1FilterShift 2
#define PM_pCOutput2Filter           93      // 2 Bits, Bit 1-0
#define     PM_pCOutput2FilterMask 0x03
#define     PM_pCOutput2FilterShift 0
#define PM_pCManualWithPresence      94      // 1 Bit, Bit 7
#define     PM_pCManualWithPresenceMask 0x80
#define     PM_pCManualWithPresenceShift 7
#define PM_pCPresenceShortNoSwitch   94      // 1 Bit, Bit 6
#define     PM_pCPresenceShortNoSwitchMask 0x40
#define     PM_pCPresenceShortNoSwitchShift 6
#define PM_pCPresenceDelayBase       95      // 2 Bits, Bit 7-6
#define     PM_pCPresenceDelayBaseMask 0xC0
#define     PM_pCPresenceDelayBaseShift 6
#define PM_pCPresenceDelayTime       95      // uint14_t
#define PM_pCPresenceShortDurationBase 97      // 2 Bits, Bit 7-6
#define     PM_pCPresenceShortDurationBaseMask 0xC0
#define     PM_pCPresenceShortDurationBaseShift 6
#define PM_pCPresenceShortDurationTime 97      // uint14_t
#define PM_pCPresenceShortDelayBase  99      // 2 Bits, Bit 7-6
#define     PM_pCPresenceShortDelayBaseMask 0xC0
#define     PM_pCPresenceShortDelayBaseShift 6
#define PM_pCPresenceShortDelayTime  99      // uint14_t
#define PM_pCBrightnessOffDelayBase  101      // 2 Bits, Bit 7-6
#define     PM_pCBrightnessOffDelayBaseMask 0xC0
#define     PM_pCBrightnessOffDelayBaseShift 6
#define PM_pCBrightnessOffDelayTime  101      // uint14_t
#define PM_pCManualFallbackDelayBase 103      // 2 Bits, Bit 7-6
#define     PM_pCManualFallbackDelayBaseMask 0xC0
#define     PM_pCManualFallbackDelayBaseShift 6
#define PM_pCManualFallbackDelayTime 103      // uint14_t
#define PM_pCBrightnessOn            105      // uint16_t
#define PM_pCBrightnessDelta         107      // uint16_t
#define PM_pCOutput1On               109      // 8 Bits, Bit 7-0
#define PM_pCOutput1OnValue          109      // uint8_t
#define PM_pCOutput1OnScene          109      // 8 Bits, Bit 7-0
#define PM_pCOutput1OnDim            109      // uint8_t
#define PM_pCOutput1Off              110      // 8 Bits, Bit 7-0
#define PM_pCOutput1OffValue         110      // uint8_t
#define PM_pCOutput1OffScene         110      // 8 Bits, Bit 7-0
#define PM_pCOutput1OffDim           110      // uint8_t
#define PM_pCOutput2On               111      // 8 Bits, Bit 7-0
#define PM_pCOutput2OnValue          111      // uint8_t
#define PM_pCOutput2OnScene          111      // 8 Bits, Bit 7-0
#define PM_pCOutput2OnDim            111      // uint8_t
#define PM_pCOutput2Off              112      // 8 Bits, Bit 7-0
#define PM_pCOutput2OffValue         112      // uint8_t
#define PM_pCOutput2OffScene         112      // 8 Bits, Bit 7-0
#define PM_pCOutput2OffDim           112      // uint8_t
#define PM_pDBrightnessAuto          113      // 2 Bits, Bit 7-6
#define     PM_pDBrightnessAutoMask 0xC0
#define     PM_pDBrightnessAutoShift 6
#define PM_pDPresenceShort           113      // 1 Bit, Bit 5
#define     PM_pDPresenceShortMask 0x20
#define     PM_pDPresenceShortShift 5
#define PM_pDLockHardwareLEDs        113      // 1 Bit, Bit 4
#define     PM_pDLockHardwareLEDsMask 0x10
#define     PM_pDLockHardwareLEDsShift 4
#define PM_pDOutput1Filter           113      // 2 Bits, Bit 3-2
#define     PM_pDOutput1FilterMask 0x0C
#define     PM_pDOutput1FilterShift 2
#define PM_pDOutput2Filter           113      // 2 Bits, Bit 1-0
#define     PM_pDOutput2FilterMask 0x03
#define     PM_pDOutput2FilterShift 0
#define PM_pDManualWithPresence      114      // 1 Bit, Bit 7
#define     PM_pDManualWithPresenceMask 0x80
#define     PM_pDManualWithPresenceShift 7
#define PM_pDPresenceShortNoSwitch   114      // 1 Bit, Bit 6
#define     PM_pDPresenceShortNoSwitchMask 0x40
#define     PM_pDPresenceShortNoSwitchShift 6
#define PM_pDPresenceDelayBase       115      // 2 Bits, Bit 7-6
#define     PM_pDPresenceDelayBaseMask 0xC0
#define     PM_pDPresenceDelayBaseShift 6
#define PM_pDPresenceDelayTime       115      // uint14_t
#define PM_pDPresenceShortDurationBase 117      // 2 Bits, Bit 7-6
#define     PM_pDPresenceShortDurationBaseMask 0xC0
#define     PM_pDPresenceShortDurationBaseShift 6
#define PM_pDPresenceShortDurationTime 117      // uint14_t
#define PM_pDPresenceShortDelayBase  119      // 2 Bits, Bit 7-6
#define     PM_pDPresenceShortDelayBaseMask 0xC0
#define     PM_pDPresenceShortDelayBaseShift 6
#define PM_pDPresenceShortDelayTime  119      // uint14_t
#define PM_pDBrightnessOffDelayBase  121      // 2 Bits, Bit 7-6
#define     PM_pDBrightnessOffDelayBaseMask 0xC0
#define     PM_pDBrightnessOffDelayBaseShift 6
#define PM_pDBrightnessOffDelayTime  121      // uint14_t
#define PM_pDManualFallbackDelayBase 123      // 2 Bits, Bit 7-6
#define     PM_pDManualFallbackDelayBaseMask 0xC0
#define     PM_pDManualFallbackDelayBaseShift 6
#define PM_pDManualFallbackDelayTime 123      // uint14_t
#define PM_pDBrightnessOn            125      // uint16_t
#define PM_pDBrightnessDelta         127      // uint16_t
#define PM_pDOutput1On               129      // 8 Bits, Bit 7-0
#define PM_pDOutput1OnValue          129      // uint8_t
#define PM_pDOutput1OnScene          129      // 8 Bits, Bit 7-0
#define PM_pDOutput1OnDim            129      // uint8_t
#define PM_pDOutput1Off              130      // 8 Bits, Bit 7-0
#define PM_pDOutput1OffValue         130      // uint8_t
#define PM_pDOutput1OffScene         130      // 8 Bits, Bit 7-0
#define PM_pDOutput1OffDim           130      // uint8_t
#define PM_pDOutput2On               131      // 8 Bits, Bit 7-0
#define PM_pDOutput2OnValue          131      // uint8_t
#define PM_pDOutput2OnScene          131      // 8 Bits, Bit 7-0
#define PM_pDOutput2OnDim            131      // uint8_t
#define PM_pDOutput2Off              132      // 8 Bits, Bit 7-0
#define PM_pDOutput2OffValue         132      // uint8_t
#define PM_pDOutput2OffScene         132      // 8 Bits, Bit 7-0
#define PM_pDOutput2OffDim           132      // uint8_t

// Communication objects per channel (multiple occurrence)
#define PM_KoOffset 50
#define PM_KoBlockSize 20
#define PM_KoKOpLux 0
#define PM_KoKOpPresence1 1
#define PM_KoKOpPresence2 2
#define PM_KoKOpSetAuto 3
#define PM_KoKOpSetManual 4
#define PM_KoKOpAktorState 5
#define PM_KoKOpLock 6
#define PM_KoKOpReset 7
#define PM_KoKOpDayPhase 8
#define PM_KoKOpLuxOn 9
#define PM_KoKOpLuxOff 10
#define PM_KoKOpPresenceDelay 11
#define PM_KoKOpScene 12
#define PM_KoKOpOutput 13
#define PM_KoKOpOutput2 14
#define PM_KoKOpIsManual 15
#define PM_KoKOpChangeDimRel 16
#define PM_KoKOpChangeDimAbs 17
#define PM_KoKOpChangeSwitch 18
#define PM_KoKOpResetExternalPM 19

#define MAIN_OpenKnxId 0xA0
#define MAIN_ApplicationNumber 0
#define MAIN_ApplicationVersion 6
#define MAIN_OrderNumber "OpenKnxPresence"
