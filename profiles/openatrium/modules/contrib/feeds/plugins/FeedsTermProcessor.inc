<?php

/**
 * @file
 * FeedsTermProcessor class.
 */

/**
 * Feeds processor plugin. Create taxonomy terms from feed items.
 */
class FeedsTermProcessor extends FeedsProcessor {
  /**
   * Define entity type.
   */
  public function entityType() {
    return 'taxonomy_term';
  }

  /**
   * Implements parent::entityInfo().
   */
  protected function entityInfo() {
    $info = parent::entityInfo();
    $info['label plural'] = t('Terms');
    $info['bundle name'] = t('Vocabulary');
    return $info;
  }

  /**
   * Creates a new term in memory and returns it.
   */
  protected function newEntity(FeedsSource $source) {
    $vocabulary = $this->vocabulary();
    $term = new stdClass();
    $term->vid = $vocabulary->vid;
    $term->vocabulary_machine_name = $vocabulary->machine_name;
    $term->format = isset($this->config['input_format']) ? $this->config['input_format'] : filter_fallback_format();
    return $term;
  }

  /**
   * Validates a term.
   */
  protected function entityValidate($term) {
    if (drupal_strlen($term->name) == 0) {
      throw new FeedsValidationException(t('Term name missing.'));
    }
  }

  /**
   * Saves a term.
   *
   * We de-array parent fields with only one item.
   * This stops leftandright module from freaking out.
   */
  protected function entitySave($term) {
    if (isset($term->parent)) {
      if (is_array($term->parent) && count($term->parent) == 1) {
        $term->parent = reset($term->parent);
      }
      if (isset($term->tid) && ($term->parent == $term->tid || (is_array($term->parent) && in_array($term->tid, $term->parent)))) {
        throw new FeedsValidationException(t("A term can't be its own child. GUID:@guid", array('@guid' => $term->feeds_item->guid)));
      }
    }
    taxonomy_term_save($term);
  }

  /**
   * Deletes a series of terms.
   */
  protected function entityDeleteMultiple($tids) {
    foreach ($tids as $tid) {
      taxonomy_term_delete($tid);
    }
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'vocabulary' => 0,
    ) + parent::configDefaults();
  }

  /**
   * Override setTargetElement to operate on a target item that is a taxonomy term.
   */
  public function setTargetElement(FeedsSource $source, $target_term, $target_element, $value) {
    switch ($target_element) {
      case 'parent':
        if (!empty($value)) {
          $terms = taxonomy_get_term_by_name($value);
          $parent_tid = '';
          foreach ($terms as $term) {
            if ($term->vid == $target_term->vid) {
              $parent_tid = $term->tid;
            }
          }
          if (!empty($parent_tid)) {
            $target_term->parent[] = $parent_tid;
          }
          else {
            $target_term->parent[] = 0;
          }
        }
        else {
          $target_term->parent[] = 0;
        }
        break;
      case 'parentguid':
        // value is parent_guid field value
        $query = db_select('feeds_item')
          ->fields('feeds_item', array('entity_id'))
          ->condition('entity_type', $this->entityType());
        $parent_tid = $query->condition('guid', $value)->execute()->fetchField();
        $target_term->parent[] = ($parent_tid) ? $parent_tid : 0;

        break;
      case 'weight':
        if (!empty($value)) {
          $weight = intval($value);
        }
        else {
          $weight = 0;
        }
        $target_term->weight = $weight;
        break;
      default:
        parent::setTargetElement($source, $target_term, $target_element, $value);
        break;
    }
  }

  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {
    $targets = parent::getMappingTargets();
    $targets += array(
      'name' => array(
        'name' => t('Term name'),
        'description' => t('Name of the taxonomy term.'),
        'optional_unique' => TRUE,
      ),
      'parent' => array(
        'name' => t('Parent: Term name'),
        'description' => t('The name of the parent taxonomy term.'),
        'optional_unique' => TRUE,
      ),
      'parentguid' => array(
        'name' => t('Parent: GUID'),
        'description' => t('The GUID of the parent taxonomy term.'),
        'optional_unique' => TRUE,
      ),
      'weight' => array(
        'name' => t('Term weight'),
        'description' => t('Weight of the taxonomy term.'),
        'optional_unique' => TRUE,
      ),
      'description' => array(
        'name' => t('Term description'),
        'description' => t('Description of the taxonomy term.'),
      ),
    );

    // Let implementers of hook_feeds_term_processor_targets() add their targets.
    try {
      self::loadMappers();
      $entity_type = $this->entityType();
      $bundle = $this->bundle();
      drupal_alter('feeds_processor_targets', $targets, $entity_type, $bundle);
    }
    catch (Exception $e) {
      // Do nothing.
    }
    return $targets;
  }

  /**
   * Get id of an existing feed item term if available.
   */
  protected function existingEntityId(FeedsSource $source, FeedsParserResult $result) {
    if ($tid = parent::existingEntityId($source, $result)) {
      return $tid;
    }

    // The only possible unique target is name.
    foreach ($this->uniqueTargets($source, $result) as $target => $value) {
      if ($target == 'name') {
        $vocabulary = $this->vocabulary();
        if ($tid = db_query("SELECT tid FROM {taxonomy_term_data} WHERE name = :name AND vid = :vid", array(':name' => $value, ':vid' => $vocabulary->vid))->fetchField()) {
          return $tid;
        }
      }
    }
    return 0;
  }

  /**
   * Return vocabulary to map to.
   */
  public function vocabulary() {
    if ($vocabulary = taxonomy_vocabulary_machine_name_load($this->bundle())) {
      return $vocabulary;
    }
    throw new Exception(t('No vocabulary defined for Taxonomy Term processor.'));
  }
}
