# Western Digital Firmware Deobfuscation Utility

This repository contains a deobfuscation utility for Western Digital firmware images, which are available online at http://www.wdc.com/wdproducts/wdsmartwareupdate/firmware.asp?id=wdfGeneric. Depending on the selected OS, the download package contains an encoded
`WDPIDS00_e.plist` or `WinPidTable_e.xml` XML file with metadata about the available firmware updates, such as the product ID, vendor ID, and presence of encryption. An example snippet extracted from `WinPidTable_e.enc` of release version `3.2.5.1` for the My Passport Essential is shown below:

```
<Device>
    <!-- Device Information  Apollo P1M/P1U R1 INIC-1607E -->
    <ProductID>070A</ProductID>
    <VendorID>1058</VendorID>
    <ProductName>My Passport Essential</ProductName>
    <ProductNameStrId>GENERIC_DEVICE_MYPASSPORT_ESSENTIAL</ProductNameStrId>
    <HasEncryption>TRUE</HasEncryption>
    <ExternalPower>FALSE</ExternalPower>
    <DismountRequired>TRUE</DismountRequired>
    <SmartWare>TRUE</SmartWare>
    <DiskInstanceId>USBSTOR\DISK&amp;VEN_WD&amp;PROD_MY_PASSPORT_070A</DiskInstanceId>
    <CdRomInstanceId>USBSTOR\CDROM&amp;VEN_WD&amp;PROD_VIRTUAL_CD_070A</CdRomInstanceId>
    <Disk1394InstanceId></Disk1394InstanceId>
    <CdRom1394InstanceId></CdRom1394InstanceId>
    <ButtonExists>FALSE</ButtonExists>
    <LEDExists>FALSE</LEDExists>
</Device>
```

Next, the updater binary will download the encoded `DeviceTable_e.xml` file from http://download.wdc.com/fwupdater/DeviceTable_e.xml, which contains a changelog of updates,download links for each binary update, as well as the updater plugins that are presumably used to flash the update over USB (e.g. JMicron, Initio, Symwave, PLX, CFU):

```
<Device>
    <!-- Device Information My Passport - Passport Onyx Hubble/Passport Edge  JMICRON-CP48 538S (USB 3.0) -->
    <ProductID>074E</ProductID>
    <VendorID>1058</VendorID>
    <ProductName>My Passport</ProductName>

    <!-- Firmware Information -->
    <SupportedFWVersion></SupportedFWVersion>
    <MinimumFWVersion></MinimumFWVersion>
    <FWReleaseDate></FWReleaseDate>
    <FWReleaseNotesStrId></FWReleaseNotesStrId>
    <FWVersion>1025</FWVersion>
    <FWFileURL>Bin/JMicron-CP48/Release-VS-1025-20130711.bin</FWFileURL>

    <!-- Device Plugin Information -->
    <DevicePluginName>JMicronDevicePlugin</DevicePluginName>
    <DevicePluginFileURL_Mac>Mac/JMicronDevicePlugin.zip</DevicePluginFileURL_Mac>
    <DevicePluginFileURL_Win>Win/JMicronDevicePlugin.zip</DevicePluginFileURL_Win>
</Device>
```
