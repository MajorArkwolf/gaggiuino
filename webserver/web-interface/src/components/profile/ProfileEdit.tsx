import React, {
  useCallback, useEffect, useMemo, useState,
} from 'react';
import {
  Box, Button, IconButton, TextField, Typography, alpha, useTheme,
} from '@mui/material';
import DoneIcon from '@mui/icons-material/Check';
import CancelIcon from '@mui/icons-material/CancelOutlined';
import CloseIcon from '@mui/icons-material/Close';
import NextIcon from '@mui/icons-material/NavigateNext';
import DeleteIcon from '@mui/icons-material/Delete';
import CreateIcon from '@mui/icons-material/AddCircle';
import PreviousIcon from '@mui/icons-material/NavigateBefore';
import {
  CurveStyle, Phase, PhaseType, Profile,
} from '../../models/profile';
import ProfileChart from '../chart/ProfileChart';
import { GlobalRestrictions } from './GlobalRestrictions';
import PhaseEditor from './PhaseEditor';
import { getIndexInRange } from '../../models/utils';

export interface ProfileEditProps {
  profile: Profile,
  onDone?: (profile: Profile) => void,
  onCancel?: () => void,
}

export function ProfileEdit({ profile, onDone = undefined, onCancel = undefined }: ProfileEditProps) {
  const [editingProfile, setEditingProfile] = useState(profile);
  const [phaseIndexSelected, setPhaseIndexSelected] = useState<number |undefined>(undefined);

  useEffect(() => {
    setEditingProfile(profile);
    setPhaseIndexSelected(undefined);
  }, [profile, setEditingProfile, setPhaseIndexSelected]);

  const deletePhase = useCallback(
    (phaseIndex: number) => {
      const newPhases = [...editingProfile.phases];
      newPhases.splice(phaseIndex, 1);
      setEditingProfile({ ...editingProfile, phases: newPhases });
      setPhaseIndexSelected(getIndexInRange(phaseIndex - 1, newPhases));
    },
    [setEditingProfile, editingProfile],
  );

  const createNewPhase = useCallback(
    (creationIndex: number) => {
      const index = Math.min(editingProfile.phases.length, Math.max(0, creationIndex)); // ensure valid range
      const newPhase:Phase = {
        skip: false,
        type: PhaseType.PRESSURE,
        target: { end: 9, curve: CurveStyle.INSTANT, time: 0 },
        stopConditions: { time: 5000 },
      };
      const newPhases = [...editingProfile.phases.slice(0, index), newPhase, ...editingProfile.phases.slice(index)];
      setEditingProfile({ ...editingProfile, phases: newPhases });
      setPhaseIndexSelected(getIndexInRange(index, newPhases));
    },
    [setEditingProfile, editingProfile],
  );

  const updatePhase = useCallback((index: number, phase:Phase) => {
    if (index < 0 || index >= editingProfile.phases.length) return;
    const phases = [...editingProfile.phases];
    phases[index] = phase;
    setEditingProfile({ ...editingProfile, phases });
  }, [editingProfile, setEditingProfile]);

  return (
    <>
      <Box>
        <ProfileEditTitle profile={editingProfile} onUpdated={setEditingProfile} onDone={onDone} onCancel={onCancel} />
      </Box>
      <Box>
        <Box position="relative">
          <ProfileChart
            profile={editingProfile}
            selectedPhaseIndex={phaseIndexSelected}
            onSelectPhase={setPhaseIndexSelected}
          />
        </Box>
        <GlobalRestrictions profile={profile} />
      </Box>
      <Box>
        <PhaseManagementBar
          profile={editingProfile}
          phaseIndexSelected={phaseIndexSelected}
          onCreatePhase={createNewPhase}
          onDeletePhase={deletePhase}
          onUpdatePhaseIndexSelected={setPhaseIndexSelected}
        />
      </Box>
      {phaseIndexSelected !== undefined && (
        <PhaseEditingSection
          title={`Phase ${phaseIndexSelected + 1}`}
          phase={editingProfile.phases[phaseIndexSelected]}
          onClose={() => setPhaseIndexSelected(undefined)}
          onUpdatePhase={(newPhase) => updatePhase(phaseIndexSelected, newPhase)}
        />
      )}
    </>
  );
}

interface PhaseManagementBarProps {
  profile: Profile;
  phaseIndexSelected: number | undefined;
  onUpdatePhaseIndexSelected: (newValue: number | undefined) => void;
  onCreatePhase: (index: number) => void;
  onDeletePhase: (undex: number) => void;
}

function PhaseManagementBar(
  {
    profile, phaseIndexSelected, onUpdatePhaseIndexSelected, onCreatePhase, onDeletePhase,
  }: PhaseManagementBarProps,
) {
  const theme = useTheme();

  const nextPhase = useCallback(
    () => onUpdatePhaseIndexSelected(
      getIndexInRange(phaseIndexSelected === undefined ? 0 : phaseIndexSelected + 1, profile.phases),
    ),
    [profile, phaseIndexSelected, onUpdatePhaseIndexSelected],
  );

  const previousPhase = useCallback(
    () => onUpdatePhaseIndexSelected(
      getIndexInRange(phaseIndexSelected === undefined ? 0 : phaseIndexSelected - 1, profile.phases),
    ),
    [profile, phaseIndexSelected, onUpdatePhaseIndexSelected],
  );

  return (
    <Box sx={{
      display: 'flex', gap: theme.spacing(1), alignItems: 'center', justifyContent: 'space-between',
    }}
    >
      {profile.phases.length > 1 && (<Button variant="outlined" onClick={previousPhase}><PreviousIcon /></Button>)}
      {phaseIndexSelected !== undefined && (
      <Box display="flex" flexGrow="1" justifyContent="center">
        <IconButton color="success" onClick={() => onCreatePhase(phaseIndexSelected)}><CreateIcon /></IconButton>
        <IconButton color="error" onClick={() => onDeletePhase(phaseIndexSelected)}><DeleteIcon /></IconButton>
        <IconButton color="success" onClick={() => onCreatePhase(phaseIndexSelected + 1)}><CreateIcon /></IconButton>
      </Box>
      )}
      {((profile.phases.length === 0) || (phaseIndexSelected === undefined)) && (
      <Box display="flex" flexGrow="1" justifyContent="center">
        <IconButton color="success" onClick={() => onCreatePhase(profile.phases.length)}><CreateIcon /></IconButton>
      </Box>
      )}
      {profile.phases.length > 1 && (<Button variant="outlined" onClick={nextPhase}><NextIcon /></Button>)}
    </Box>
  );
}

interface ProfileEditTitleProps extends ProfileEditProps {
  onUpdated: (profile:Profile) => void,
}

function ProfileEditTitle(
  {
    profile,
    onUpdated,
    onDone = undefined,
    onCancel = undefined,
  }: ProfileEditTitleProps,
) {
  const theme = useTheme();
  const updateName = useCallback((name:string) => onUpdated({ ...profile, name }), [profile, onUpdated]);

  return (
    <Box sx={{
      display: 'flex',
      alignItems: 'center',
      justifyContent: 'space-between',
      flexWrap: 'wrap',
      mb: theme.spacing(2),
    }}
    >
      <Typography variant="h6">
        <TextField variant="standard" value={profile.name || 'New profile'} onChange={(e) => updateName(e.target.value)}></TextField>
      </Typography>
      <Box sx={{ display: 'flex', alignItems: 'center', columnGap: theme.spacing(1) }}>
        {onDone && <IconButton size="small" color="success" onClick={() => onDone(profile)}><DoneIcon fontSize="inherit" /></IconButton>}
        {onCancel && <IconButton size="small" color="error" onClick={onCancel}><CancelIcon fontSize="inherit" /></IconButton>}
      </Box>
    </Box>
  );
}

interface PhaseEditingSectionProps {
  title: string
  phase: Phase;
  onClose: () => void;
  onUpdatePhase: (phase: Phase) => void;
}

function PhaseEditingSection({
  title, phase, onClose, onUpdatePhase,
}: PhaseEditingSectionProps) {
  const theme = useTheme();
  return (
    <Box sx={{
      mt: theme.spacing(2),
      background: alpha(phase.type === PhaseType.FLOW
        ? theme.palette.flow.main : theme.palette.pressure.main, 0.1),
      p: 2,
      borderRadius: theme.spacing(2),
    }}
    >
      <Box sx={{
        mb: 1, display: 'flex', alignItems: 'center', justifyContent: 'space-between',
      }}
      >
        <Typography>{title}</Typography>
        <IconButton size="small" onClick={onClose}><CloseIcon /></IconButton>
      </Box>
      <PhaseEditor phase={phase} onChange={onUpdatePhase} />
    </Box>
  );
}
