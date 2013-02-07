package com.automatak.dnp3;

public class OutstationConfig {

    /**
     * Outstation constructor with reasonable defaults
     */
    public OutstationConfig()
    {

    }

    /**
     * The maximum number of controls the slave will attempt to process from a single APDU, defaults to 1
     */
    public int maxControls = 1;

    /**
     * if true, fully disables unsolicited mode as if the slave didn't support it, defaults to false
     */
    public boolean disableUnsol = false;

    /**
     * controls what unsol classes are enabled by default. defaults to Class 1, 2, & 3
     *
     * Use PointClass.getMask to set this value
     */
    public int unsolMask = PointClass.ALL_EVENTS.toInt();

    /**
     * if true, the outstation will request time synchronization on an interval. Defaults to false.
     */
    public boolean allowTimeSync = false;


    /**
     * The period of time sync interval in milliseconds. Defaults to 10 minutes (10 * 60 * 1000)
     */
    public long timeSyncPeriodMs = 10 * 60 * 1000;

    /**
     * The amount of time in milliseconds the slave will wait before sending new unsolicited data ( <= 0 == immediately, no delay). Defaults to 200ms.
     */
    public  long unsolPackDelayMs = 200;

    /**
     * How long the slave will wait in milliseconds before retrying an unsuccessful unsolicited response  Defaults to 2000ms.
     */
    public long unsolRetryDelayMs = 2000;

    /**
     * The maximum fragment size the slave will use for data it sends. Defaults to 2048.
     */
    public int maxFragSize = 2048;

    /**
     * The number of objects to store in the VtoWriter queue. Defaults to 1024.
     */
    public int vtoWriterQueueSize = 1024;


    /**
     * The number of binary events the slave will buffer before overflowing (defaults to 1000)
     */
    int maxBinaryEvents = 1000;

    /**
     * The number of analog events the slave will buffer before overflowing (defaults to 1000)
     */
    int maxAnalogEvents = 1000;

    /**
     * The number of counter events the slave will buffer before overflowing (defaults to 1000)
     */
    int maxCounterEvents = 1000;

    /**
     * The number of vto events the slave will buffer before overflowing (defaults to 100)
     */
    int maxVtoEvents = 100;

    /**
     * The default group/variation to use for static binary responses (default 1:2)
     */
    public final GroupVariation staticBinaryInput  = new GroupVariation(1, 2);

    /**
     * The default group/variation to use for static analog responses (default 30:1)
     */
    public final GroupVariation staticAnalogInput = new GroupVariation(30, 1);

    /**
     * The default group/variation to use for static counter responses (default 20:1)
     */
    public final GroupVariation staticCounter = new GroupVariation(20, 1);

    /**
     * The default group/variation to use for static AnalogOutput status responses (default 40:1)
     */
    public final GroupVariation staticAnalogOutputStatus =  new GroupVariation(40, 1);

    /**
     * The default group/variation to use for binary event responses (default 2:1)
     */
    public final GroupVariation eventBinaryInput = new GroupVariation(2, 1);

    /**
     * The default group/variation to use for analog event responses (default 32:1)
     */
    public final GroupVariation eventAnalogInput = new GroupVariation(32, 1);

    /**
     * The default group/variation to use for counter event responses (default 22:1)
     */
    public final GroupVariation eventCounter = new GroupVariation(22, 1);

    /**
     * The default group/variation to use for VTO event responses (default 113, 0)
     */
    public final GroupVariation eventVto = new GroupVariation(113, 0);

}
