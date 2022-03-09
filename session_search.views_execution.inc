<?php

/**
 * @file
 * Session Search views execution file.
 */

use Drupal\views\Plugin\views\query\QueryPluginBase;
use Drupal\views\ViewExecutable;

/**
 * Implements hook_views_query_alter().
 */
function session_search_views_query_alter(ViewExecutable $view, QueryPluginBase $query) {
  if ($view->id() == 'sessions' && !empty($view->exposed_raw_input['combine'])) {
    // Get the terms and synonyms.
    $terms = [];
    $config = \Drupal::state()->get('session_search_terms');
    $lines = explode(PHP_EOL, $config);
    foreach ($lines as $line) {
      $termSynonyms = explode('|', $line);
      $term = strtolower(trim($termSynonyms[0]));
      $terms[$term] = [];
      $synonyms = explode(',', $termSynonyms[1]);
      foreach ($synonyms as $s) {
        $terms[$term][] = strtolower(trim($s));
      }
    }

    // If there are any synonyms for the search value, act.
    if (in_array(trim(strtolower($view->exposed_raw_input['combine'])), array_keys($terms))) {
      $query->setGroupOperator('OR');
      $count = 1;
      foreach ($terms[strtolower($view->exposed_raw_input['combine'])] as $sy) {
        $count++;
        $query->setWhereGroup('AND', $count);
        $query->addWhere($count, "node_field_data.status", 1, "=");
        $query->addWhere($count, "node_field_data.type", "session", "=");
        $query->addWhere($count, "node_field_data.title", "%" . $sy . "%", "LIKE");

        $count++;
        $query->setWhereGroup('AND', $count);
        $query->addWhere($count, "node_field_data.status", 1, "=");
        $query->addWhere($count, "node_field_data.type", "session", "=");
        $query->addWhere($count, "node__body.body_value", "%" . $sy . "%", "LIKE");
      }
    }
  }
}
