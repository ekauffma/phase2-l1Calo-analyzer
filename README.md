# Phase 2 L1 Calo Analyzer

## Setup

Set up `CMSSW_11_1_7` (use in conjunction with https://github.com/skkwan/cmssw/blob/devel-Phase2RCTCluster/L1Trigger/L1CaloTrigger/plugins/) and clone this repo

## Each time you run...

Make sure the `L1Trigger/L1CaloTrigger` area is compiled, since this analyzer loads and calls the modules from that area.

If analyzing the CMSSW emulator, make sure the `python/` config file uses the `L1EGamma`... cluster collection.
If analyzing the firmware-based emulator, make sure the `python/` config file uses the `Phase2L1EGamma`... cluster collection.
(Otherwise the clusters won't show up)

Then do `cmsenv` and `cmsRun` the analyzer `.py` of the CMSSW or firmware-based emulator.

The analyzer creates several outputs:
    * A `.root` file named `L1EventDisplay` (etc.) - this should be used in the event display code
    * A `.txt` file (containing whatever `.txt` printouts specified in the `L1Trigger/L1CaloTrigger` plugins scripts)
    * A `.root` file (containing the outputs generated by the `L1Trigger/L1CaloTrigger` plugins scripts)

Copy the `L1EventDisplay` ROOT files into the event display repo: https://github.com/skkwan/phase2-l1t-eventDisplay and proceed there
