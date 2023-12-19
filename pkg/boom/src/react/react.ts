import Reconciler from 'react-reconciler'
import { DefaultEventPriority } from 'react-reconciler/constants'

type Type = 'Window' | 'Node';

type Props = Record<string, (string | number)>;

type Container = object;

type Instance = {
    type: 'Window';
    window: Window;
} | {
    type: 'Node';
    node: Node;
};

type TextInstance = {
    type: 'Text';
    node: Node;
};

type SuspenseInstance = object;

type HydratableInstance = object;

type PublicInstance = object;

type HostContext = object;

type UpdatePayload = object;

type ChildSet = object;

type TimeoutHandle = object;

type NoTimeout = null;

const reconciler = Reconciler<
    Type,
    Props,
    Container,
    Instance,
    TextInstance,
    SuspenseInstance,
    HydratableInstance,
    PublicInstance,
    HostContext,
    UpdatePayload,
    ChildSet,
    TimeoutHandle,
    NoTimeout
>({
    noTimeout: null,
    supportsMutation: true,
    supportsPersistence: false,
    supportsMicrotasks: true,
    isPrimaryRenderer: true,
    warnsIfNotActing: true,
    supportsHydration: false,
    createInstance(type, props, rootContainer, hostContext, internalHandle) {
        if (type === 'Node') {
            const node = new Node();
            for (const [ prop, value ] of Object.entries(props)) {
                // @ts-ignore
                node[prop] = value;
            }
            return { type, node };
        } else if (type === 'Window') {
            const window = new Window();
            for (const [ prop, value ] of Object.entries(props)) {
                // @ts-ignore
                window[prop] = value;
            }
            return { type, window };
        } else {
            throw new Error(`Instance type "${type}" not supported`);
        }
    },
    createTextInstance(text, rootContainer, hostContext, internalHandle) {
        const node = new Node();
        node.text = text;
        return { type: 'Text', node };
    },
    appendInitialChild(parentInstance, child) {
        if (parentInstance.type === 'Node') {
            if ((child.type === 'Node')
            || (child.type === 'Text')) {
                parentInstance.node.addChild(child.node);
            }
        } else if (parentInstance.type === 'Window') {
            if ((child.type === 'Node')
            || (child.type === 'Text')) {
                /** TODO: add nodes to the window */
            }
        }
    },
    finalizeInitialChildren(instance, type, props, rootContainer, hostContext) {
        return true;
    },
    prepareUpdate(instance, type, oldProps, newProps, rootContainer, hostContext) {
        return {};
    },
    shouldSetTextContent(type, props) {
        if (type === 'Node') return true;
        else return false;
    },
    getRootHostContext(rootContainer) {
        return null;
    },
    getChildHostContext(parentHostContext, type, rootContainer) {
        return parentHostContext;
    },
    getPublicInstance(instance) {
        return instance;
    },
    prepareForCommit(containerInfo) {
        return null;
    },
    resetAfterCommit(containerInfo) {

    },
    preparePortalMount(containerInfo) {

    },
    scheduleTimeout(fn: (...args: unknown[]) => unknown, delay) {
        return setTimeout(fn, delay ?? 0);
    },
    cancelTimeout(id) {
        clearTimeout(id);
    },
    scheduleMicrotask(fn: () => unknown) {

    },
    getCurrentEventPriority() {
        return DefaultEventPriority;
    },
    getInstanceFromNode(node) {
        return null;
    },
    beforeActiveInstanceBlur() {

    },
    afterActiveInstanceBlur() {

    },
    prepareScopeUpdate(scopeInstance, instance) {

    },
    getInstanceFromScope(scopeInstance) {
        return null;
    },
    detachDeletedInstance(node) {

    },
    appendChild(parentInstance, child) {

    },
    appendChildToContainer(container, child) {

    },
    insertBefore(parentInstance, child, beforeChild) {

    },
    insertInContainerBefore(container, child, beforeChild) {

    },
    removeChild(parentInstance, child) {

    },
    removeChildFromContainer(container, child) {

    },
    resetTextContent(instance) {

    },
    commitTextUpdate(textInstance, oldText, newText) {

    },
    commitMount(instance, type, props, internalInstanceHandle) {

    },
    commitUpdate(instance, updatePayload, type, prevProps, nextProps, internalHandle) {

    },
    hideInstance(instance) {

    },
    hideTextInstance(textInstance) {

    },
    unhideInstance(instance, props) {

    },
    unhideTextInstance(textInstance, text) {

    },
    clearContainer(container) {

    },
    cloneInstance(instance, updatePayload, type, oldProps, newProps, internalInstanceHandle, keepChildren, recyclableInstance) {
        return {} as any;
    },
    createContainerChildSet(container) {
        return [];
    },
    appendChildToContainerChildSet(childSet, child) {

    },
    finalizeContainerChildren(container, newChildren) {

    },
    replaceContainerChildren(container, newChildren) {

    },
    cloneHiddenInstance(instance, type, props, internalInstanceHandle) {
        return {} as any;
    },
    cloneHiddenTextInstance(instance, text, internalInstanceHandle) {
        return {} as any;
    },
    canHydrateInstance(instance, type, props) {
        return null;
    },
    canHydrateTextInstance(instance, text) {
        return null;
    },
    canHydrateSuspenseInstance(instance) {
        return null;
    },
    isSuspenseInstancePending(instance) {
        return false;
    },
    isSuspenseInstanceFallback(instance) {
        return false;
    },
    registerSuspenseInstanceRetry(instance, callback: () => void) {

    },
    getNextHydratableSibling(instance) {
        return null;
    },
    getFirstHydratableChild(parentInstance) {
        return null;
    },
    hydrateInstance(instance, type, props, rootContainerInstance, hostContext, internalInstanceHandle) {
        return null;
    },
    hydrateTextInstance(textInstance, text, internalInstanceHandle) {
        return false;
    },
    hydrateSuspenseInstance(suspenseInstance, internalInstanceHandle) {

    },
    getNextHydratableInstanceAfterSuspenseInstance(suspenseInstance) {
        return null;
    },
    getParentSuspenseInstance(targetInstance) {
        return null;
    },
    commitHydratedContainer(container) {

    },
    commitHydratedSuspenseInstance(suspenseInstance) {

    },
    didNotMatchHydratedContainerTextInstance(parentContainer, textInstance, text) {

    },
    didNotMatchHydratedTextInstance(parentType, parentProps, parentInstance, textInstance, text) {

    },
    didNotHydrateContainerInstance(parentContainer, instance) {

    },
    didNotHydrateInstance(parentType, parentProps, parentInstance, instance) {

    },
    didNotFindHydratableContainerInstance(parentContainer, type, props) {

    },
    didNotFindHydratableContainerTextInstance(parentContainer, text) {

    },
    didNotFindHydratableContainerSuspenseInstance(parentContainer) {

    },
    didNotFindHydratableInstance(parentType, parentProps, parentInstance, type, props) {

    },
    didNotFindHydratableTextInstance(parentType, parentProps, parentInstance, text) {

    },
    didNotFindHydratableSuspenseInstance(parentType, parentProps, parentInstance) {

    },
    errorHydratingContainer(parentContainer) {

    },
})

export const render = (app: JSX.Element) => {
    // reconciler.createContainer()
}