const eCtrlLv = {
    CTRL_LV_PROGRESS: [document.getElementById('div-ctrl-progress')],
    CTRL_LV_GMDIR   : [document.getElementById('div-ctrl-gmdir')],
    CTRL_LV_OPTIONS : [document.getElementById('div-ctrl-options')],
  /*CTRL_LV_EXTRACT : [document.getElementById('div-ctrl-extract')],
    CTRL_LV_APPLY   : [document.getElementById('div-ctrl-apply')],*/
    CTRL_LV_PATCH   : [document.getElementById('div-ctrl-patch')],
    CTRL_LV_SETTING : [document.getElementById('div-ctrl-setting')]
};

class Control {
    move(lv) {
        for (const k in eCtrlLv) {
            const doc = eCtrlLv[k][0];
            const display = doc.style.display;

            if (display !== 'none') {
                this.#mLastDisplay.set(doc, display);
            }

            doc.style.display = 'none';
        }

        const display = this.#mLastDisplay.get(lv[0]);
        lv[0].style.display = (display == null ? 'block' : display);
    }

    constructor() {
        this.#mLastDisplay = new Map();
    }

    #mLastDisplay;
    static INSTANCE = new Control();
}

const ePatchMode = {
  PATCH_MODE_EXTRACT: [0],
  PATCH_MODE_APPLY  : [1]
};

class Patch {
    setMode(lv) {
        this.#mMode = lv[0];
    }

    getMode() {
        return this.#mMode;
    }

    mPatchDir= '';
    #mMode = 0;
    static INSTANCE = new Patch();
}


document.getElementById('bt-ctrl-gmdir-manually').addEventListener('click', e => {
    Control.INSTANCE.move(eCtrlLv.CTRL_LV_PROGRESS);
    window.SET_GMDIR_MANUALLY();
});
document.getElementById('bt-ctrl-gmdir-automatically').addEventListener('click', e => {
    Control.INSTANCE.move(eCtrlLv.CTRL_LV_PROGRESS);
    window.SET_GMDIR_AUTOMATICALLY();
});
document.getElementById('bt-ctrl-options-extract').addEventListener('click', e => {
    Patch.INSTANCE.setMode(ePatchMode.PATCH_MODE_EXTRACT);
    Control.INSTANCE.move(eCtrlLv.CTRL_LV_PATCH);

    const desc = document.getElementById('p-ctrl-patch-desc');
    desc.innerHTML = 'Extract data from game';
    const alert = document.getElementById('p-ctrl-patch-alert');
    alert.innerHTML = 'Please perform the game in its original, unmodified state.'
    const start = document.getElementById('bt-ctrl-patch-start');
    start.innerHTML = 'Start Extract'
    start.disabled = false;

    const selectDiv = document.getElementById('div-ctrl-patch-select-dir');
    selectDiv.style.display = 'none';
});
document.getElementById('bt-ctrl-options-apply').addEventListener('click', e => {
    Patch.INSTANCE.setMode(ePatchMode.PATCH_MODE_APPLY);
    Control.INSTANCE.move(eCtrlLv.CTRL_LV_PATCH);

    const desc = document.getElementById('p-ctrl-patch-desc');
    desc.innerHTML = 'Apply patch to game';
    const alert = document.getElementById('p-ctrl-patch-alert');
    alert.innerHTML = 'Backup your save data before patch.'
    const start = document.getElementById('bt-ctrl-patch-start');
    start.innerHTML = 'Start Patch'
    start.disabled = true;

    Patch.INSTANCE.mPatchDir = '';

    const selDesc = document.getElementById('p-ctrl-patch-continue');
    selDesc.innerHTML = 'Please select the folder containing the patch files.'
    const selectDiv = document.getElementById('div-ctrl-patch-select-dir');
    selectDiv.style.display = 'flex';
});
document.getElementById('bt-ctrl-options-setting').addEventListener('click', e => {
   Control.INSTANCE.move(eCtrlLv.CTRL_LV_GMDIR);
});

document.getElementById('bt-ctrl-patch-select-dir').addEventListener('click', e => {
    Control.INSTANCE.move(eCtrlLv.CTRL_LV_PROGRESS);
    window.SELECT_PATCH_DATA_DIR();
});
document.getElementById('bt-ctrl-patch-start').addEventListener('click', e => {
    Control.INSTANCE.move(eCtrlLv.CTRL_LV_PROGRESS);

    const pm = Patch.INSTANCE.getMode();
    switch (pm) {
        case ePatchMode.PATCH_MODE_EXTRACT[0]: {
            window.PATCH_EXTRACT();
            break;
        }
        case ePatchMode.PATCH_MODE_APPLY[0]: {
            window.PATCH_APPLY(Patch.INSTANCE.mPatchDir);
            break;
        }
    }
});
document.getElementById('bt-ctrl-patch-back').addEventListener('click', e => {
   Control.INSTANCE.move(eCtrlLv.CTRL_LV_OPTIONS);
});

function _selectedPatchDataDir(dir) {
    Patch.INSTANCE.mPatchDir = dir;
    Control.INSTANCE.move(eCtrlLv.CTRL_LV_PATCH);

    if (dir === '') {
        return;
    }

    const start = document.getElementById('bt-ctrl-patch-start');
    start.disabled = false;
}

function _finishPatch() {
    Control.INSTANCE.move(eCtrlLv.CTRL_LV_OPTIONS);
}