
struct ParameterData {
	uint16_t PID;
	uint8_t PDLSize;
	uint8_t DataType;
	uint8_t CommandClass;
	uint8_t Type;
	uint8_t Unit;
	uint8_t Prefix;
	uint32_t MinValidValue;
	uint32_t MaxValidValue;
	uint32_t DefaultValue;
	unsigned char Description[32];
};

const uint16_t S4WRD_COLOR_PARAMS[] = {
				E120_STATUS_MESSAGES,
				E120_SUPPORTED_PARAMETERS,
				E120_PARAMETER_DESCRIPTION,
				E120_DEVICE_INFO,
				E120_DEVICE_MODEL_DESCRIPTION,
				E120_MANUFACTURER_LABEL,
				E120_DEVICE_LABEL,
				E120_FACTORY_DEFAULTS,
				E120_SOFTWARE_VERSION_LABEL,
				E120_DMX_PERSONALITY,
				E120_DMX_PERSONALITY_DESCRIPTION,
				E120_DMX_START_ADDRESS,
				E120_SLOT_INFO,
				E120_SLOT_DESCRIPTION,
				E120_DEFAULT_SLOT_VALUE,
				E120_SENSOR_DEFINITION,
				E120_SENSOR_VALUE,
				E120_IDENTIFY_DEVICE,
				E120_RESET_DEVICE,
				E120_CAPTURE_PRESET,
				E120_PRESET_PLAYBACK,
				E120_ETC_SEQUENCE_PLAYBACK,
				E120_ETC_SEQUENCE_CONFIG,
//				E120_ETC_LOW_POWER_TIMEOUT,
//				E120_ETC_LOW_POWER_TIMEOUT_DESCRIPTION,
				E120_ETC_LED_ENUM_FREQUENCY,
				E120_ETC_LED_ENUM_FREQUENCY_DESCRIPTION,
				E120_ETC_RGBI_PRESETCONFIG,
				E120_ETC_PREPAREFORSOFTWAREDOWNLOAD
};


const uint16_t CS_PAR_ZOOM_PARAMS[] = {
				E120_STATUS_MESSAGES,
				E120_SUPPORTED_PARAMETERS,
				E120_PARAMETER_DESCRIPTION,
				E120_DEVICE_INFO,
				E120_DEVICE_MODEL_DESCRIPTION,
				E120_MANUFACTURER_LABEL,
				E120_DEVICE_LABEL,
				E120_FACTORY_DEFAULTS,
				E120_SOFTWARE_VERSION_LABEL,
				E120_DMX_PERSONALITY,
				E120_DMX_PERSONALITY_DESCRIPTION,
				E120_DMX_START_ADDRESS,
				E120_SLOT_INFO,
				E120_SLOT_DESCRIPTION,
				E120_DEFAULT_SLOT_VALUE,
				E120_SENSOR_DEFINITION,
				E120_SENSOR_VALUE,
				E120_IDENTIFY_DEVICE,
				E120_RESET_DEVICE,
				E120_CAPTURE_PRESET,
				E120_PRESET_PLAYBACK,
				E120_ETC_SEQUENCE_PLAYBACK,
				E120_ETC_SEQUENCE_CONFIG,
//				E120_ETC_LOW_POWER_TIMEOUT,
//				E120_ETC_LOW_POWER_TIMEOUT_DESCRIPTION,
				E120_ETC_LED_ENUM_FREQUENCY,
				E120_ETC_LED_ENUM_FREQUENCY_DESCRIPTION,
				E120_ETC_RGBI_PRESETCONFIG,
				E120_ETC_PREPAREFORSOFTWAREDOWNLOAD
};

const uint16_t ALL_PARAMS[] = {
				E120_STATUS_MESSAGES,
				E120_SUPPORTED_PARAMETERS,
				E120_PARAMETER_DESCRIPTION,
				E120_DEVICE_INFO,
				E120_DEVICE_MODEL_DESCRIPTION,
				E120_MANUFACTURER_LABEL,
				E120_DEVICE_LABEL,
				E120_FACTORY_DEFAULTS,
				E120_SOFTWARE_VERSION_LABEL,
				E120_DMX_PERSONALITY,
				E120_DMX_PERSONALITY_DESCRIPTION,
				E120_DMX_START_ADDRESS,
				E120_SLOT_INFO,
				E120_SLOT_DESCRIPTION,
				E120_DEFAULT_SLOT_VALUE,
				E120_SENSOR_DEFINITION,
				E120_SENSOR_VALUE,
				E120_IDENTIFY_DEVICE,
				E120_RESET_DEVICE,
				E120_CAPTURE_PRESET,
				E120_PRESET_PLAYBACK,
				E120_ETC_SEQUENCE_PLAYBACK,
				E120_ETC_SEQUENCE_CONFIG,
				E120_ETC_LOW_POWER_TIMEOUT,
				E120_ETC_LOW_POWER_TIMEOUT_DESCRIPTION,
				E120_ETC_LED_ENUM_FREQUENCY,
				E120_ETC_LED_ENUM_FREQUENCY_DESCRIPTION,
				E120_ETC_RGBI_PRESETCONFIG,
				E120_ETC_PREPAREFORSOFTWAREDOWNLOAD
};

const uint16_t MANF_PARAMS[] = {
				E120_ETC_SEQUENCE_PLAYBACK,
				E120_ETC_SEQUENCE_CONFIG,
				E120_ETC_LOW_POWER_TIMEOUT,
				E120_ETC_LOW_POWER_TIMEOUT_DESCRIPTION,
				E120_ETC_LED_ENUM_FREQUENCY,
				E120_ETC_LED_ENUM_FREQUENCY_DESCRIPTION,
				E120_ETC_RGBI_PRESETCONFIG,
				E120_ETC_PREPAREFORSOFTWAREDOWNLOAD
};

const ParameterData MANF_PARAM_DATA[]{
	{ E120_ETC_SEQUENCE_PLAYBACK,               2, E120_DS_UNSIGNED_WORD,         E120_CC_GET_SET, 0    , E120_UNITS_NONE , E120_PREFIX_NONE,   0,    5,    0, "Sequence Play Back"},
	{ E120_ETC_SEQUENCE_CONFIG,                77, E120_DS_ETC_SEQUENCECONFIG,    E120_CC_GET_SET, 0    , E120_UNITS_NONE , E120_PREFIX_NONE,   1,	  5,    1, "Sequence Config"},
	{ E120_ETC_LOW_POWER_TIMEOUT,               1, E120_DS_UNSIGNED_BYTE,         E120_CC_GET_SET, 0    , E120_UNITS_NONE , E120_PREFIX_NONE,   0,    5,    0, "Low Power Timeout"},
	{ E120_ETC_LOW_POWER_TIMEOUT_DESCRIPTION,  33, E120_DS_ETC_PARAMETER_DESC,    E120_CC_GET,     0    , E120_UNITS_NONE , E120_PREFIX_NONE,   0,    5,    0, "Low Power Timeout Desc"},
	{ E120_ETC_LED_ENUM_FREQUENCY,              1, E120_DS_UNSIGNED_BYTE,         E120_CC_GET_SET, 0    , E120_UNITS_NONE , E120_PREFIX_NONE,   0,    1,    0, "LED Frequency"},
	{ E120_ETC_LED_ENUM_FREQUENCY_DESCRIPTION, 33, E120_DS_ETC_PARAMETER_DESC,    E120_CC_GET,     0    , E120_UNITS_NONE , E120_PREFIX_NONE,   0,    1,    0, "LED Frequency Desc"},
	{ E120_ETC_RGBI_PRESETCONFIG,              11, E120_DS_ETC_RGBI_PRESETCONFIG, E120_CC_GET_SET, 0    , E120_UNITS_NONE , E120_PREFIX_NONE,   1,   12,    1, "Preset Config"},
	{ E120_ETC_CCT_PRESETCONFIG,               18, E120_DS_ETC_CCT_PRESETCONFIG,  E120_CC_GET_SET, 0    , E120_UNITS_NONE , E120_PREFIX_NONE,   1,   12,    1, "CCT Preset Config"},
	{ E120_ETC_PREPAREFORSOFTWAREDOWNLOAD,      1, E120_DS_UNSIGNED_BYTE,         E120_CC_SET,     0    , E120_UNITS_NONE , E120_PREFIX_NONE,   0,    1,    0, "Upgrade"},
};

