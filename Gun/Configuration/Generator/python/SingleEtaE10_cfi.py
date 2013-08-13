import FWCore.ParameterSet.Config as cms

generator = cms.EDProducer("FlatRandomPtGunProducer",
    PGunParameters = cms.PSet(
        PartID = cms.vint32(221),
        MaxEta = cms.double(3.0),
        MaxPhi = cms.double(3.14159265359),
        MinEta = cms.double(-3.0),
        MinPt = cms.double(1.0),
        MinPhi = cms.double(-3.14159265359), ## in radians
        MaxPt = cms.double(15.0)
    ),
    Verbosity = cms.untracked.int32(0), ## set to 1 (or greater)  for printouts

    psethack = cms.string('single eta E 10'),
    AddAntiParticle = cms.bool(False),
    firstRun = cms.untracked.uint32(1)
)
