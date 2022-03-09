<?php

namespace Drupal\session_search\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\State\StateInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Search settings class.
 */
class SessionSearchAdminForm extends FormBase {

  /**
   * The state storage object.
   *
   * @var \Drupal\Core\State\StateInterface
   */
  protected $state;

  /**
   * Constructor.
   *
   * @param \Drupal\Core\State\StateInterface $state
   *   The state storage object.
   */
  public function __construct(StateInterface $state) {
    $this->state = $state;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('state')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'session_search_admin_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {

    $form['session_search_terms'] = [
      '#type' => 'textarea',
      '#title' => $this->t('Terms and Synonyms'),
      '#description' => $this->t("Please enter in this format:</br> term1|synonym1,synonym2,synonym3</br>term2|synonym1,synonym2,synonym3"),
      '#default_value' => $this->state->get('session_search_terms'),
    ];

    $form['actions']['submit'] = [
      '#type' => 'submit',
      '#value' => $this->t('Submit'),
    ];

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $this->state->set('session_search_terms', $form_state->getValue('session_search_terms'));
  }

}
