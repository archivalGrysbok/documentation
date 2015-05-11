<?php

/**
 * @file
 * Utility functions for defining collection bundles.
 */

/**
 * Defines bundles (content types) for this module.
 */
function islandora_collection_define_bundles() {
  module_load_include('inc', 'islandora_dcterms', 'include/fields');

  $t = get_t();

  // Create basic_image bundle.
  $collection_content_type = array(
    'type' => ISLANDORA_COLLECTION_BUNDLE,
    'name' => $t('Collection'),
    'base' => 'node_content',
    'description' => $t('A collection in Fedora'),
    'custom' => 1,
    'modified' => 1,
    'locked' => 0,
    'disabled' => 0,
  );

  $collection_content_type = node_type_set_defaults($collection_content_type);

  $status = node_type_save($collection_content_type);

  $t_args = array('%name' => $collection_content_type->name);

  if ($status == SAVED_UPDATED) {
    drupal_set_message($t('Updated %name content type.', $t_args));
  }
  elseif ($status == SAVED_NEW) {
    drupal_set_message($t('Created %name content type.', $t_args));
  }

  // Add thumbnail field.
  if (field_info_field(ISLANDORA_TN_FIELD)) {
    $tn_field_instance = array(
      'field_name' => ISLANDORA_TN_FIELD,
      'entity_type' => 'node',
      'bundle' => ISLANDORA_COLLECTION_BUNDLE,
      'label' => $t("Thumbnail"),
      'description' => $t("A thumbnail for the Fedora resource"),
      'required' => FALSE,
    );
    field_create_instance($tn_field_instance);
    drupal_set_message($t('Field %name was created successfully', array('%name' => ISLANDORA_TN_FIELD)));
  }

  // Add MODS field.
  if (field_info_field(ISLANDORA_MODS_FIELD)) {
    $mods_field_instance = array(
      'field_name' => ISLANDORA_MODS_FIELD,
      'entity_type' => 'node',
      'bundle' => ISLANDORA_COLLECTION_BUNDLE,
      'label' => $t("MODS"),
      'description' => $t("A MODS record for the Fedora resource"),
      'required' => FALSE,
    );
    field_create_instance($mods_field_instance);
    drupal_set_message($t('Field %name was created successfully', array('%name' => ISLANDORA_MODS_FIELD)));
  }

  // Add dcterms fields.
  islandora_dcterms_attach_fields_to_bundle(ISLANDORA_COLLECTION_BUNDLE);
}