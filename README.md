# Samsung SSD Firmware Deobfuscation Utility

This repository contains a deobfuscation utility for Samsung SSD firmware images, which are available online at https://www.samsung.com/global/business/semiconductor/minisite/SSD/global/html/support/downloads.html. The download packages usually contain two files: `DSRD.enc` and `<firmware version>.enc`. The former is actually an XML file that contains metadata about the firmware update (used by the e.g. the Magician update tool), such as the specific model and serial numbers it applies to, the path to the input firmware binary, and the previous and new firmware versions. An example snippet extracted from `DSRD.enc` of firmware version `DXM06B0Q` for the 840 Pro is shown below:

```
<SSD>
<SN>ALL</SN>
<MOD>Samsung SSD 840 PRO Series</MOD>
<CURFW>DXM05B0Q</CURFW>
<NEWFW>DXM06B0Q</NEWFW>
<IFW>DXM06B0Q.bin</IFW>
<PWR>T</PWR>
</SSD>
```

Preliminary analysis of the actual firmware binaries suggests that some are ARM little-endian, but I have not taken a close look.
