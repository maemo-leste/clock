schemasdir = $(GCONF_SCHEMA_FILE_DIR)
schemas_DATA = clock.schemas

defaultsdir = ${data}/usr/share/gconf/defaults
defaults_DATA = 10_libclockcore0-0

cuddir = ${sysconfdir}/osso-cud-scripts
cud_SCRIPTS = clockcore-clean.sh

backupconfdir = ${sysconfdir}/osso-backup/applications
backupconf_DATA = worldclock.conf

backupprebackupdir = ${sysconfdir}/osso-backup/pre-backup.d/
backupprebackup_SCRIPTS = clock.prebackup.sh

backuprestoredir = ${sysconfdir}/osso-backup/restore.d/always/
backuprestore_SCRIPTS = clock.restore.sh
